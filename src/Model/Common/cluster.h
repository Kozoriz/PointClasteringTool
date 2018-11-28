#ifndef CLUSTER_H
#define CLUSTER_H

#include "utils/structures/matrix3.h"

#include <pcl/PointIndices.h>
#include "Model/Common/pointcloud.h"

namespace utils {
namespace file_system {
class File;
} // namespace file_system
} // namespace utils

class Cluster : public pcl::PointIndices
{
public:
  Cluster(const utils::String& cluster_name, const utils::String& pc_name, const utils::String& datetime_clustered);
  Cluster(const utils::String& path);

  const utils::String& GetClusterName() const;
  const utils::String& GetPCName() const;
  const utils::String& GetDateTimeClustered() const;

  void SaveTo(const utils::String& path) const;

  void LoadFrom(const utils::String& path);
  void LoadFrom(utils::file_system::File& file);

public:
  PointCloud::PointType cluster_maxs;
  PointCloud::PointType cluster_mins;
  void OnPointAppended(PointCloud::PointType& p);


private:
  utils::String m_cluster_name;
  utils::String m_pc_name;
  utils::String m_datetime_clustered;
};
#endif // CLUSTER_H
