#ifndef CLUSTER_H
#define CLUSTER_H

#include "utils/structures/matrix3.h"

namespace utils {
namespace file_system {
class File;
} // namespace file_system
} // namespace utils

class Cluster : public utils::structures::Matrix3
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
  utils::positions::Location3 cluster_center;
  Double dispersion = 0;

private:
  utils::String m_cluster_name;
  utils::String m_pc_name;
  utils::String m_datetime_clustered;
};
#endif // CLUSTER_H
