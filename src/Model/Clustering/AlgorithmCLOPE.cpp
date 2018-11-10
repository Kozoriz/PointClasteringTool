#include "AlgorithmCLOPE.h"
#include "utils/logger.h"
#include "utils/date_time.h"

#include <climits>

CREATE_LOGGER("Clustering")

#include <math.h>

Double getPercentageInRange(Double value, Double min, Double max)
{
  Double result = (value - min) / (max - min);
  return std::isnan(result) ? 0.0 : result * 100.0;
}

AlgorithmCLOPE::~AlgorithmCLOPE() {}

// calculates how far all points located from center of cluster (average) concentration(profit) = 1/this_value
Double AlgorithmCLOPE::calculateProfitWithPoint(Cluster& cluster, const Cluster::ContainerType::key_type& new_point, bool save_to_cluster)// misha VSE HUYNA davai po novoi
{
  // calculating current center mass
  const int size = static_cast<int>(cluster.size());
  Int64 x_sum = cluster.cluster_center.x_ * size;
  Int64 y_sum = cluster.cluster_center.y_ * size;
  Int64 z_sum = cluster.cluster_center.z_ * size;

  x_sum += new_point.x_;
  y_sum += new_point.y_;
  z_sum += new_point.z_;

  // recalculated center with new point
  const int new_size = size + 1;
  x_sum /= new_size;
  y_sum /= new_size;
  z_sum /= new_size;

  // recalculating disspersion
  Int64 d_sum = 0;
  for(auto& c_point : cluster)
  {
    d_sum += (std::pow(x_sum-c_point.x_,2) + std::pow(y_sum-c_point.y_,2) + std::pow(z_sum-c_point.z_,2));
  }

  d_sum /= new_size;
  d_sum = sqrt(d_sum);

  if(save_to_cluster)
  {
    cluster.cluster_center.x_ = x_sum;
    cluster.cluster_center.y_ = y_sum;
    cluster.cluster_center.z_ = z_sum;

    cluster.dispersion = d_sum;
//    LOG_DEBUG("Disp for : " << cluster.GetClusterName() << " set to : " << cluster.dispersion);
  }
  return d_sum;
}

utils::Vector<utils::SharedPtr<Cluster> > AlgorithmCLOPE::RunTask(const PointCloud &pc)
{
  LOG_AUTO_TRACE();

  utils::String date_clustered = utils::date_time::GetDateTimeString("%F_%T");
  utils::Vector<utils::SharedPtr<Cluster> > clusters;
  uint32_t point_ind = 0;
  for(auto& point : pc)
  {
    utils::SharedPtr<Cluster> max_profit_cluster;
    Double max_profit_deviation = INT_MAX;
    for(auto& cluster_sptr :clusters)
    {
      Double new_profit = calculateProfitWithPoint(*(cluster_sptr.get()), point);
      Double profit_dev = new_profit - cluster_sptr->dispersion;
      if(profit_dev < max_profit_deviation)
      {
        max_profit_deviation = profit_dev;
        max_profit_cluster = cluster_sptr;
      }
    }
    if(!max_profit_cluster || (false)) // TODO use app_settings <max_disp_change_perc>
    {
      max_profit_cluster = utils::make_shared<Cluster>("cluster_" + std::to_string(clusters.size()), pc.GetPCName(), date_clustered);
      max_profit_cluster->dispersion = 0;
      max_profit_cluster->cluster_center = point;
      clusters.push_back(max_profit_cluster);
    }
    if(++point_ind % 1000 == 0)
    {
      LOG_TRACE("Added to " << max_profit_cluster->GetClusterName()
                << " disp : " << max_profit_cluster->dispersion
                << " point " << point.ToString()
                << " ind : " << point_ind);
    }
    calculateProfitWithPoint(*max_profit_cluster.get(), point, true);
    max_profit_cluster->AddPoint(point);
  }
  return clusters;
}

utils::String AlgorithmCLOPE::GetName() const
{
  return "CLOPE";
}
