#include "pointcloud.h"

#include "utils/logger.h"
#include "utils/file_system.h"
#include "utils/containers/converters.h"

#include <pcl/point_types.h>

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
  utils::String filename = m_cloud_name + ".pointcloud";

  File file(path + filename);
  file.Open(File::OpenMode::Write);
  if(file.IsOpened())
  {
    for(auto point : *this)
    {
      file.WriteLine(utils::ConvertToString(point));
    }
    file.Close();
  }
}

void PointCloud::LoadFrom(const utils::String &path)
{
  LOG_AUTO_TRACE();
  utils::file_system::File file(path);
  LoadFrom(file);
}

void PointCloud::LoadFrom(utils::file_system::File &file)
{
  LOG_AUTO_TRACE();
  using namespace utils;
  file.Open(file_system::File::OpenMode::Read);

  if(!file.IsOpened())
  {
    LOG_ERROR("Cant open " << file.GetFullPath());
    return;
  }

  m_cloud_name = file_system::File::GetFileName(file.GetFullPath());
  m_is_clustered = true; // if saved in app working dir then already saved

  utils::String line;
  while(!file.IsEof())
  {
    line = file.ReadLine();
//    LOG_TRACE(line);
    if(line.empty()) continue;
    this->push_back(convertTo<pcl::PointXYZRGB>(line));
  }

  file.Close();
  LOG_DEBUG("Loaded " << size() << " points from " << file.GetFullPath());
}

