#include "PointCloudManager.h"

#include "utils/file_system.h"
#include "utils/logger.h"
#include "utils/containers/converters.h"

CREATE_LOGGER("PointCloudManager")

const utils::String sWorkingDir = "/home/andrii/PointClouds/";

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
    m_stats_manager->StartMeasurement();
    m_clusters = clustering_algo->RunTask(cloud);
    m_stats_manager->StopMeasurement();
    m_stats_manager->SaveMeasurementData(sWorkingDir + cloud.GetPCName()); // use app settings
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
