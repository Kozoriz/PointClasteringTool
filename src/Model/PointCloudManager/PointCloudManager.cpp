#include "PointCloudManager.h"

#include "utils/file_system.h"
#include "utils/logger.h"

CREATE_LOGGER("PointCloudManager")

void PointCloudManager::LoadNewCloud(utils::String &sPath)
{
  utils::file_system::File PCFile(sPath);
  PCFile.Open(utils::file_system::File::OpenMode::Read);
  if(!PCFile.IsOpened())
  {

  }
}

void PointCloudManager::RunClasteringProcess(PointCloudManager::PointCloud &cloud)
{

}
