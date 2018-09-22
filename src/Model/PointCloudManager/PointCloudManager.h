#pragma once

#include "utils/pointers/unique_ptr.h"
#include "utils/pointers/shared_prt.h"
#include "utils/containers/vector.h"
#include "utils/containers/string.h"
#include "utils/structures/matrix3.h"
#include "utils/date_time.h"

#include "Model/Statistics/StatisticsManager.h"
#include "Model/Clustering/ClusteringAlgo.h"


class Cluster : public utils::structures::Matrix3
{
public:
  Cluster(const utils::String& cluster_name, const utils::String& pc_name, const utils::String& datetime_clustered);

  const utils::String& GetClusterName() const;
  const utils::String& GetPCName() const;
  const utils::String& GetDateTimeClustered() const;
private:
  const utils::String m_cluster_name;
  const utils::String& m_pc_name;
  const utils::String m_datetime_clustered;
};

class PointCloud : public utils::structures::Matrix3
{
public:
  PointCloud(const utils::String& pc_name);

  const utils::String& GetPCName() const;
  bool IsClustered() const;
  void SetClustered(bool is_clustered = true);

private:
  const utils::String m_cloud_name;
  bool m_is_clustered;
};

class PointCloudManager
{
public:
  virtual ~PointCloudManager() {}
  const PointCloud& LoadNewCloud(utils::String& sPath);
  void RunClasteringProcess(const PointCloud& cloud);

private:
  utils::SharedPtr<StatisticsManager> m_stats_manager;
  utils::Vector<utils::SharedPtr<ClusteringAlgo> > m_clustering_algos;
  utils::Vector<utils::SharedPtr<PointCloud> > m_point_clouds;
  utils::Vector<utils::SharedPtr<Cluster> > m_clusters;
};
