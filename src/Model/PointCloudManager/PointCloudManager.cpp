#include "PointCloudManager.h"

#include "utils/file_system.h"
#include "utils/logger.h"
#include "utils/containers/converters.h"

CREATE_LOGGER("PointCloudManager")

const PointCloud& PointCloudManager::LoadNewCloud(utils::String &sPath)
{
  LOG_AUTO_TRACE()
  utils::file_system::File PCFile(sPath);
  PCFile.Open(utils::file_system::File::OpenMode::Read);
  if(!PCFile.IsOpened())
  {
    LOG_ERROR("Cannot open file : " << sPath);
  }

  utils::String line;
  utils::SharedPtr<PointCloud> pc = utils::make_shared<PointCloud>(sPath);
  do
  {
    line = PCFile.ReadLine();
    pc->AddPoint(utils::convertTo<utils::positions::Location3>(line));
  } while(!line.empty());

  m_point_clouds.push_back(pc);
  return *pc;
}

void PointCloudManager::RunClasteringProcess(const PointCloud &cloud)
{
  LOG_AUTO_TRACE()
  for(auto clustering_algo : m_clustering_algos)
  {
//    m_stats_manager->RunTask(clustering_algo->GetName());
//    clustering_algo->RunTask(cloud, m_clusters);
//    m_stats_manager->StopTask(clustering_algo->GetName());
//    m_stats_manager->SaveMeasurementData("some_path");
  }
}

PointCloud::PointCloud(const utils::String &pc_name)
  : m_cloud_name(pc_name)
  , m_is_clustered(false){}

const utils::String &PointCloud::GetPCName() const
{
  return m_cloud_name;
}

bool PointCloud::IsClustered() const
{
  return m_is_clustered;
}

void PointCloud::SetClustered(bool is_clustered)
{
  m_is_clustered = is_clustered;
}

Cluster::Cluster(const utils::String &cluster_name, const utils::String &pc_name, const utils::String &datetime_clustered)
  : m_cluster_name(cluster_name)
  , m_pc_name(pc_name)
  , m_datetime_clustered(datetime_clustered){}

const utils::String &Cluster::GetClusterName() const
{
  return m_cluster_name;
}

const utils::String &Cluster::GetPCName() const
{
  return m_pc_name;
}

const utils::String &Cluster::GetDateTimeClustered() const
{
  return m_datetime_clustered;
}
