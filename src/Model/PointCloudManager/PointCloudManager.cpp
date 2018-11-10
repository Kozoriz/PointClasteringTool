#include "PointCloudManager.h"

#include "utils/file_system.h"
#include "utils/logger.h"
#include "utils/containers/converters.h"

#include "Model/Clustering/AlgorithmMST.h"
#include "Model/Clustering/AlgorithmCLOPE.h"

CREATE_LOGGER("PointCloudManager")

PointCloudManager::PointCloudManager(ApplicationSettings& settings, StatisticsManager& stats_manager)
  : m_settings(settings)
  , m_stats_manager(stats_manager)
{
  LOG_AUTO_TRACE();
  utils::file_system::Directory dir(m_settings.get_working_dir());
  utils::file_system::Directory::FilesList files = dir.GetFilesList(true); // uncomment if needed to reopen already clustered
  for(auto file : files)
  {
    if("pointcloud" == file->GetExt())
    {
      utils::SharedPtr<PointCloud> pc = utils::make_shared<PointCloud>("");
      m_point_clouds.push_back(pc);

      pc->LoadFrom(*file);
    }
    else if("cluster" == file->GetExt())
    {
      utils::SharedPtr<Cluster> cluster = utils::make_shared<Cluster>("");
      m_clusters.push_back(cluster);

      cluster->LoadFrom(*file);
    }
  }

//  m_clustering_algos.push_back(utils::make_shared<AlgorithmCLOPE>());
  m_clustering_algos.push_back(utils::make_shared<AlgorithmMST>());
}

const PointCloud& PointCloudManager::LoadNewCloud(utils::String &sPath)
{
  LOG_AUTO_TRACE();

  const utils::String sFileName = utils::file_system::File::GetFileName(sPath);
  utils::file_system::Directory::RecursiveCreate(utils::file_system::ExtendPath(m_settings.get_working_dir(), sFileName));
  utils::file_system::File::Copy(sPath, utils::file_system::ExtendPath(m_settings.get_working_dir(), sFileName, sFileName) + ".pointcloud");

  utils::SharedPtr<PointCloud> pc = utils::make_shared<PointCloud>("");
  m_point_clouds.push_back(pc);

  pc->LoadFrom(sPath);

  return *pc;
}

void PointCloudManager::RunClasteringProcess(const PointCloud &cloud)
{
  LOG_AUTO_TRACE()
  for(auto clustering_algo : m_clustering_algos)
  {
    m_stats_manager.StartMeasurement();
    m_clusters = clustering_algo->RunTask(cloud);
    m_stats_manager.StopMeasurement();
    m_stats_manager.SaveMeasurementData(utils::file_system::ExtendPath(m_settings.get_working_dir(), cloud.GetPCName(), clustering_algo->GetName()));
    SaveClusters();
  }
}

void PointCloudManager::SaveClusters()
{
  LOG_AUTO_TRACE()
  for(auto cluster : m_clusters)
  {
      cluster->SaveTo(m_settings.get_working_dir());
  }
}

const PointCloudManager::PointClouds &PointCloudManager::GetPointClouds() const
{
  return m_point_clouds;
}

const PointCloudManager::Clusters &PointCloudManager::GetClusters() const
{
  return m_clusters;
}

const utils::structures::Matrix3 &PointCloudManager::GetMatrix(utils::String &filename) const
{
  LOG_AUTO_TRACE();

  auto it_pc = std::find_if(m_point_clouds.begin(), m_point_clouds.end(),
               [&filename](utils::SharedPtr<PointCloud> p)
  {
    return filename == p->GetPCName();
  });
  if(m_point_clouds.end() != it_pc)
  {
    return **it_pc;
  }

  auto it_cl = std::find_if(m_clusters.begin(), m_clusters.end(),
               [&filename](utils::SharedPtr<Cluster> p)
  {
    return filename == p->GetPCName();
  });
  if(m_clusters.end() != it_cl)
  {
    return **it_cl;
  }
  return utils::structures::Matrix3();
}

const utils::Vector<utils::String> PointCloudManager::GetCloudNames() const
{
  utils::Vector<utils::String> v;
  for(auto& cloud : m_point_clouds)
  {
    v.push_back(cloud->GetPCName());
  }
  for(auto& cloud : m_clusters)
  {
    v.push_back(cloud->GetClusterName());
  }
  return v;
}
