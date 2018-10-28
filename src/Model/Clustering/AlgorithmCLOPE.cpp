#include "AlgorithmCLOPE.h"
#include "utils/logger.h"
#include "utils/date_time.h"


CREATE_LOGGER("Clustering")

AlgorithmCLOPE::~AlgorithmCLOPE() {}

// calculates how far all points located from center of cluster (average) concentration(profit) = 1/this_value
Double AlgorithmCLOPE::calculateProfitWithPoint(const Cluster& cluster, const Cluster::ContainerType::key_type& new_point)
{
  Int64 x_sum = 0;
  Int64 y_sum = 0;
  Int64 z_sum = 0;

  for(auto& c_point : cluster)
  {
    x_sum += c_point.x_;
    y_sum += c_point.y_;
    z_sum += c_point.z_;
  }
  LOG_TRACE(std::to_string(x_sum) << " " << std::to_string(y_sum) << " "<< std::to_string(z_sum) );
  x_sum += new_point.x_;
  y_sum += new_point.y_;
  z_sum += new_point.z_;

  x_sum /= cluster.Size() + 1;
  y_sum /= cluster.Size() + 1;
  z_sum /= cluster.Size() + 1;

  LOG_TRACE(std::to_string(x_sum) << " " << std::to_string(y_sum) << " "<< std::to_string(z_sum) );
  Int64 d_sum = 0;
  for(auto& c_point : cluster)
  {
    d_sum += (std::pow(x_sum-c_point.x_,2) + std::pow(y_sum-c_point.y_,2) + std::pow(z_sum-c_point.z_,2));
  }
  LOG_TRACE(std::to_string(d_sum));
  d_sum /= cluster.Size() + 1;
  LOG_TRACE(std::to_string(d_sum));

  return sqrt(d_sum);
}

void RecalculateConcentration(utils::SharedPtr<Cluster> cluster)
{
  Int64 x_sum = 0;
  Int64 y_sum = 0;
  Int64 z_sum = 0;

  for(auto& c_point : *cluster)
  {
    x_sum += c_point.x_;
    y_sum += c_point.y_;
    z_sum += c_point.z_;
  }

  x_sum /= cluster->Size();
  y_sum /= cluster->Size();
  z_sum /= cluster->Size();

  Int64 d_sum = 0;
  for(auto& c_point : *cluster)
  {
    d_sum += (std::pow(x_sum-c_point.x_,2) + std::pow(y_sum-c_point.y_,2) + std::pow(z_sum-c_point.z_,2));
  }
  d_sum /= cluster->Size();

  cluster->profit = sqrt(d_sum);
}

utils::Vector<utils::SharedPtr<Cluster> > AlgorithmCLOPE::RunTask(const PointCloud &pc)
{
  LOG_AUTO_TRACE();

  utils::String date_clustered = utils::date_time::GetDateTimeString("%F_%T");
  utils::Vector<utils::SharedPtr<Cluster> > clusters;
  for(auto& point : pc)
  {
    utils::SharedPtr<Cluster> max_profit_cluster;
    Double max_profit_deviation = INT_MAX;
    for(auto& cluster_sptr :clusters)
    {
      Double new_profit = calculateProfitWithPoint(*(cluster_sptr.get()), point);
      Double profit_dev = new_profit - cluster_sptr->profit;
      LOG_TRACE("profit dev " << cluster_sptr->GetClusterName() << " = " << std::to_string(profit_dev) );
      if(profit_dev < max_profit_deviation)
      {
        max_profit_deviation = profit_dev;
        max_profit_cluster = cluster_sptr;
      }
    }
    if(!max_profit_cluster || max_profit_deviation > 10) // TODO use app_settings <max_cluster radius>
    {
      max_profit_cluster = utils::make_shared<Cluster>("cluster_" + std::to_string(clusters.size()), pc.GetPCName(), date_clustered);
      max_profit_cluster->profit = 0;
      clusters.push_back(max_profit_cluster);
      LOG_DEBUG("Created new cluster " << max_profit_cluster->GetPCName() << " -> " << max_profit_cluster->GetClusterName());
    }
    LOG_TRACE("Added to " << max_profit_cluster->GetClusterName() << " dev : " << std::to_string(max_profit_deviation) << " point " << point.ToString());
    max_profit_cluster->AddPoint(point);
    RecalculateConcentration(max_profit_cluster);
  }
  return clusters;
}

utils::String AlgorithmCLOPE::GetName() const
{
  return "CLOPE";
}
