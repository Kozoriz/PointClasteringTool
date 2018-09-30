#pragma once

#include "utils/pointers/shared_prt.h"
#include "utils/containers/vector.h"

#include "Model/Statistics/StatisticsManager.h"
#include "Model/Clustering/ClusteringAlgo.h"
#include "Model/Common/cluster.h"
#include "Model/Common/pointcloud.h"

class PointCloudManager
{
public:
  virtual ~PointCloudManager() {}
  const PointCloud& LoadNewCloud(utils::String& sPath);
  void RunClasteringProcess(const PointCloud& cloud);
  void SaveClusters();

private:
  utils::SharedPtr<StatisticsManager> m_stats_manager;
  utils::Vector<utils::SharedPtr<ClusteringAlgo> > m_clustering_algos;
  utils::Vector<utils::SharedPtr<PointCloud> > m_point_clouds;
  utils::Vector<utils::SharedPtr<Cluster> > m_clusters;
};
