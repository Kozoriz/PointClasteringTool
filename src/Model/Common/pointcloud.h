#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "utils/structures/matrix3.h"

class PointCloud : public utils::structures::Matrix3
{
public:
  PointCloud(const utils::String& pc_name);

  const utils::String& GetPCName() const;
  bool IsClustered() const;
  void SetClustered(bool is_clustered = true);

private:
  const utils::String m_cloud_name;
  bool m_is_clustered;
};

#endif // POINTCLOUD_H
