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
  typedef utils::Vector<SharedPtr<PointCloud> > PointClouds;
  typedef utils::Vector<Cluster> Clusters;
public:
  PointCloudManager(ApplicationSettings& settings, StatisticsManager& stats_manager);
  PointCloud::Ptr LoadNewCloud(utils::String& sPath);
  void RunClasteringProcess(PointCloud::Ptr cloud);
  void SaveClusters();

  const PointClouds& GetPointClouds() const;
  const Clusters& GetClusters() const;

  PointCloud::ConstPtr GetMatrix(utils::String& filename) const;
  const utils::Vector<utils::String> GetCloudNames() const;

private:
  const ApplicationSettings& m_settings;
  StatisticsManager& m_stats_manager;
  utils::Vector<SharedPtr<ClusteringAlgo> > m_clustering_algos;
  PointClouds m_point_clouds;
  Clusters m_clusters;
};
