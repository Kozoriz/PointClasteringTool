#include "AlgorithmCLOPE.h"
#include "utils/logger.h"
#include "utils/date_time.h"

#include <iomanip>
#include <climits>
#include <float.h>

CREATE_LOGGER("Clustering")

#include <math.h>

Double getPercentageInRange(Double value, Double min, Double max)
{
  Double result = (value - min) / (max - min);
  return std::isnan(result) ? 0.0 : result * 100.0;
}

AlgorithmCLOPE::AlgorithmCLOPE(const ApplicationSettings &settings)
  : m_settings(settings)
{
}

AlgorithmCLOPE::~AlgorithmCLOPE() {}

float  calculateSlopeChange(PointCloud::Ptr pc, Cluster& cluster, PointCloud::PointType& point)
{
  PointCloud::PointType& max = cluster.cluster_maxs;
  PointCloud::PointType& min = cluster.cluster_mins;

  float x_diff = std::max(std::max(point.x-max.x, min.x-point.x), 0.f);
  float y_diff = std::max(std::max(point.y-max.y, min.y-point.y), 0.f);
  float z_diff = std::max(std::max(point.z-max.z, min.z-point.z), 0.f);

//  printf("%.6f %.6f %.6f %.6f\n", point.x, max.x, min.x, x_diff + y_diff + z_diff);

  return x_diff + y_diff + z_diff;
}

utils::Vector<Cluster> AlgorithmCLOPE::RunTask(PointCloud::Ptr pc)
{
  LOG_AUTO_TRACE();

  uncolorAllPoints(pc);

  utils::String date_clustered = utils::date_time::GetDateTimeString("%F_%T");
  utils::Vector<Cluster> clusters;
  int point_ind = 0;
  int best_cluster_ind = 0;
  for(auto& point : *pc)
  {
    Cluster* p_best_profit_cluster = nullptr;
    float min_cluster_change = FLT_MAX;
    int clust_ind = 0;
    for(auto&  cluster : clusters)
    {
      float slope_change = calculateSlopeChange(pc, cluster, point);
      if(min_cluster_change > slope_change)
      {
        min_cluster_change = slope_change;
        p_best_profit_cluster = &cluster;
        best_cluster_ind = clust_ind;
      }
      ++clust_ind;
    }

    if(!p_best_profit_cluster || min_cluster_change > sensivity)
    {
//      LOG_TRACE("Created : " << std::setprecision(10) <<  min_cluster_change << " > " <<  m_settings.get_clope_sensivity());
      clusters.push_back(Cluster("cluster", pc->GetPCName(),date_clustered));
      p_best_profit_cluster = &clusters[clusters.size()-1];
      best_cluster_ind = clusters.size()-1;
    }

    // cluster saves only indexes of points inside cloud
    p_best_profit_cluster->indices.push_back(point_ind++);
    p_best_profit_cluster->OnPointAppended(point);

    point.label = best_cluster_ind;

    /*if(point_ind % 100000 == 0)*/ LOG_TRACE("Processed : " << point_ind << " clusters : " << clusters.size() );
  }
  LOG_TRACE("Found clusters " << clusters.size());
  // need to paint @pc according to clustered indices
  std::vector<uint32_t> colors;
  colors.resize((float)clusters.size()*1.2, 0);

  srand(rand());
  for(PointCloud::PointType& point : *pc)
  {
    uint32_t rgba = colors[point.label];
    if(rgba == 0)
    {
      point.r = rand() % 255;
      point.g = rand() % 255;
      point.b = rand() % 255;
      point.a = 255;
      colors[point.label] = point.rgba;
      LOG_DEBUG("New color : " << (int)point.r << " "<< (int)point.g << " "<< (int)point.b << " label " << point.label);
    }
    point.rgba = rgba;
//    LOG_DEBUG("Point " << point << " label " << point.label);
  }

  return clusters;
}

utils::String AlgorithmCLOPE::GetName() const
{
  return "CLOPE";
}

void AlgorithmCLOPE::SetParams(std::map<utils::String, double> params)
{
  sensivity = params["sensitivity"];

  LOG_DEBUG("sensivity : " << sensivity);

}
