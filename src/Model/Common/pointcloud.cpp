#include "pointcloud.h"

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
