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
  typedef utils::Vector<utils::SharedPtr<PointCloud> > PointClouds;
  typedef utils::Vector<utils::SharedPtr<Cluster> > Clusters;
public:
  PointCloudManager(ApplicationSettings& settings, StatisticsManager& stats_manager);
  const PointCloud& LoadNewCloud(utils::String& sPath);
  void RunClasteringProcess(const PointCloud& cloud);
  void SaveClusters();

  const PointClouds& GetPointClouds() const;
  const Clusters& GetClusters() const;

  const utils::structures::Matrix3& GetMatrix(utils::String& filename) const;
  const utils::Vector<utils::String> GetCloudNames() const;

private:
  const ApplicationSettings& m_settings;
  StatisticsManager& m_stats_manager;
  utils::Vector<utils::SharedPtr<ClusteringAlgo> > m_clustering_algos;
  PointClouds m_point_clouds;
  Clusters m_clusters;
};
