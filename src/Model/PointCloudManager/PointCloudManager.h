#pragma once

#include "utils/pointers/shared_prt.h"
#include "utils/containers/vector.h"

#include "Model/Statistics/StatisticsManager.h"
#include "Model/Clustering/ClusteringAlgo.h"
#include "Model/Common/cluster.h"
#include "Model/Common/pointcloud.h"
#include "Model/Settings/applicationsettings.h"

class PointCloudManager
{
public:
  PointCloudManager(ApplicationSettings& settings, StatisticsManager& stats_manager);
  const PointCloud& LoadNewCloud(utils::String& sPath);
  void RunClasteringProcess(const PointCloud& cloud);
  void SaveClusters();

private:
  const ApplicationSettings& m_settings;
  StatisticsManager& m_stats_manager;
  utils::Vector<utils::SharedPtr<ClusteringAlgo> > m_clustering_algos;
  utils::Vector<utils::SharedPtr<PointCloud> > m_point_clouds;
  utils::Vector<utils::SharedPtr<Cluster> > m_clusters;
};
