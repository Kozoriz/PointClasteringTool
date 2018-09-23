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
    m_stats_manager->StartMeasurement();
    m_clusters = clustering_algo->RunTask(cloud);
    m_stats_manager->StopMeasurement();
    m_stats_manager->SaveMeasurementData("some_path"); // use app settings
    SaveClusters(cloud.GetPCName());
  }
}

void PointCloudManager::SaveClusters(const utils::String& pc_name)
{

}
