#pragma once

#include "utils/pointers/shared_prt.h"
#include "utils/containers/vector.h"

#include "Model/Statistics/StatisticsManager.h"
#include "Model/Clustering/ClusteringAlgo.h"
#include "Model/Common/cluster.h"
#include "Model/Common/pointcloud.h"
#include "Model/Settings/applicationsettings.h"

class Controller;

class PointCloudManager
{
public:
  typedef utils::Vector<SharedPtr<PointCloud> > PointClouds;
  typedef utils::Vector<Cluster> Clusters;
public:
  PointCloudManager(ApplicationSettings& settings, StatisticsManager& stats_manager);
  PointCloud::Ptr LoadNewCloud(utils::String& sPath);
  void RunClasteringProcess(PointCloud::Ptr cloud, const utils::String &sAlgo, std::map<utils::String, double> params);
  void SaveClusters();

  const PointClouds& GetPointClouds() const;
  const Clusters& GetClusters() const;

  PointCloud::Ptr GetMatrix(const utils::String& filename) const;
  const utils::Vector<utils::String> GetCloudNames() const;


  void SetController(Controller* p_controller) {m_controller = p_controller;}

private:
  const ApplicationSettings& m_settings;
  StatisticsManager& m_stats_manager;
  utils::Vector<SharedPtr<ClusteringAlgo> > m_clustering_algos;
  PointClouds m_point_clouds;
  Clusters m_clusters;

  Controller* m_controller = nullptr;
};
