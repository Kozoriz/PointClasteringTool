#include "PointCloudManager.h"

#include "utils/file_system.h"
#include "utils/logger.h"
#include "utils/containers/converters.h"

#include "Model/Clustering/AlgorithmMST.h"
#include "Model/Clustering/AlgorithmCLOPE.h"

CREATE_LOGGER("PointCloudManager")

const utils::String sWorkingDir = "/home/andrii/PointClouds/";

PointCloudManager::PointCloudManager(const utils::String &working_dir, StatisticsManager& stats_manager)
  : m_stats_manager(stats_manager)
{
  utils::file_system::Directory dir(working_dir);
  utils::file_system::Directory::FilesList files = dir.GetFilesList(true);
  for(auto file : files)
  {
    if(".pc" == file->GetExt(file->GetFullPath()))
    {
      utils::SharedPtr<PointCloud> pc = utils::make_shared<PointCloud>("");
      m_point_clouds.push_back(pc);

      pc->LoadFrom(*file);
    }
    else if(".cluster" == file->GetExt(file->GetFullPath()))
    {
      utils::SharedPtr<Cluster> cluster = utils::make_shared<Cluster>("");
      m_clusters.push_back(cluster);

      cluster->LoadFrom(*file);
    }
  }

  m_clustering_algos.push_back(utils::make_shared<AlgorithmCLOPE>());
  m_clustering_algos.push_back(utils::make_shared<AlgorithmMST>());
}

const PointCloud& PointCloudManager::LoadNewCloud(utils::String &sPath)
{
  LOG_AUTO_TRACE();

  const utils::String sFileName = utils::file_system::File::GetFileName(sPath);
  utils::file_system::File::Copy(sPath, sWorkingDir + sFileName + "/" + sFileName + ".pc");

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
    m_stats_manager.SaveMeasurementData(sWorkingDir + "/" + cloud.GetPCName() + "/" + clustering_algo->GetName() + "/"); // use app settings
    SaveClusters();
  }
}

void PointCloudManager::SaveClusters()
{
  LOG_AUTO_TRACE()
  for(auto cluster : m_clusters)
  {
      cluster->SaveTo(sWorkingDir); // use app settings
  }
}
