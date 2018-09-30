#include "pointcloud.h"

#include "utils/logger.h"
#include "utils/file_system.h"
#include "utils/containers/converters.h"

CREATE_LOGGER("PointCloud")

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

void PointCloud::SaveTo(const utils::String &path) const
{
  LOG_AUTO_TRACE();
  using namespace utils::file_system;
  utils::String filename = m_cloud_name + ".pc";

  File file(path + filename);
  file.Open(File::OpenMode::Write);
  if(file.IsOpened())
  {
    for(auto point : *this)
    {
      file.WriteLine(point.ToString());
    }
    file.Close();
  }
}

void PointCloud::LoadFrom(const utils::String &path)
{
  LOG_AUTO_TRACE();
  using namespace utils;
  file_system::File file(path);
  file.Open(file_system::File::OpenMode::Read);

  if(!file.IsOpened())
  {
    LOG_ERROR("Cant open " << path);
    return;
  }

  m_cloud_name = file_system::File::GetFileName(path);
  m_is_clustered = true; // if saved in app working dir then already saved

  utils::String line;
  do
  {
    line = file.ReadLine();
    AddPoint(utils::convertTo<utils::positions::Location3>(line));
  } while(!line.empty());

  file.Close();
  LOG_DEBUG("Loaded " << Size() << " points from " << path);
}

