#include "pointcloud.h"

#include "utils/logger.h"
#include "utils/file_system.h"

#include <pcl/point_types.h>
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
  utils::String filename = m_cloud_name + ".pointcloud";

  File file(path + filename);
  file.Open(File::OpenMode::Write);
  if(file.IsOpened())
  {
    for(auto point : *this)
    {
      file.WriteLine(utils::ConvertToString<PointCloud::PointType&>(point));
    }
    file.Close();
  }
}

void PointCloud::ShiftTo(int x, int y, int z)
{
  int min_x = INT_MAX;
  int min_y = INT_MAX;
  int min_z = INT_MAX;
  for(auto point : *this)
  {
    if(min_x > point.x) min_x = point.x;
    if(min_y > point.y) min_y = point.y;
    if(min_z > point.z) min_z = point.z;
  }
  for(auto point : *this)
  {
    point.x = point.x - min_x + x;
    point.y = point.y - min_y + y;
    point.z = point.z - min_z + z;
  }

  LOG_TRACE("Shifted : " << min_x << " " << min_y << " " << min_z);
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
//  m_is_clustered = true; // if saved in app working dir then already saved

  utils::String line;
  while(!file.IsEof())
  {
    line = file.ReadLine();
//    LOG_TRACE(line);
    if(line.empty()) continue;
    PointCloud::PointType point = convertTo<PointCloud::PointType>(line);
//    printf("%.6f %.6f %.6f ", point.x, point.y, point.z);
//    LOG_TRACE(point);
    this->push_back(point);
  }

  file.Close();
  LOG_DEBUG("Loaded " << size() << " points from " << file.GetFullPath());
}

