#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "utils/structures/matrix3.h"

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>


namespace utils{
namespace file_system{
class File;
} // namespace file_system
} // namespace utils


template<class T>
using SharedPtr = boost::shared_ptr<T>;

class PointCloud : public pcl::PointCloud<pcl::PointXYZRGBL>
{
public:
  typedef SharedPtr<PointCloud> Ptr;
  typedef SharedPtr<const PointCloud> ConstPtr;

  PointCloud(const utils::String& pc_name);

  const utils::String& GetPCName() const;
  bool IsClustered() const;
  void SetClustered(bool is_clustered = true);

  void LoadFrom(const utils::String &path);
  void LoadFrom(utils::file_system::File& file);
  void SaveTo(const utils::String &path) const;

  void ShiftTo(int x, int y, int z);

private:
  utils::String m_cloud_name;
  bool m_is_clustered;
};

namespace{
void uncolorAllPoints(PointCloud::Ptr pc)
{
  for(auto& point : *pc)
  {
    point.rgba = UINT32_MAX;
  }
}
} // namespace

#endif // POINTCLOUD_H
