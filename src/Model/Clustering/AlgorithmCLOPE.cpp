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

  utils::String date_clustered = utils::date_time::GetDateTimeString("%F_%T");
  utils::Vector<Cluster> clusters;
  int point_ind = 0;
  for(auto& point : *pc)
  {
    Cluster* p_best_profit_cluster = nullptr;
    float min_cluster_change = FLT_MAX;
    for(auto&  cluster : clusters)
    {
      float slope_change = calculateSlopeChange(pc, cluster, point);
      if(min_cluster_change > slope_change)
      {
        min_cluster_change = slope_change;
        p_best_profit_cluster = &cluster;
      }
    }

    if(!p_best_profit_cluster || min_cluster_change > m_settings.get_clope_sensivity())
    {
//      LOG_TRACE("Created : " << std::setprecision(10) <<  min_cluster_change << " > " <<  m_settings.get_clope_sensivity());
      clusters.push_back(Cluster("cluster", pc->GetPCName(),date_clustered));
      p_best_profit_cluster = &clusters[clusters.size()-1];
    }

    // cluster saves only indexes of points inside cloud
    p_best_profit_cluster->indices.push_back(point_ind++);
    p_best_profit_cluster->OnPointAppended(point);
    if(point_ind % 100000 == 0) LOG_TRACE("Processed : " << point_ind << " clusters : " << clusters.size() );
  }
  LOG_TRACE("Found clusters " << clusters.size());
  // need to paint @pc according to clustered indices
  return clusters;
}

utils::String AlgorithmCLOPE::GetName() const
{
  return "CLOPE";
}
