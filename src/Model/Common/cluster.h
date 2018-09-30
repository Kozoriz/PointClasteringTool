#ifndef CLUSTER_H
#define CLUSTER_H

#include "utils/structures/matrix3.h"

class Cluster : public utils::structures::Matrix3
{
public:
  Cluster(const utils::String& cluster_name, const utils::String& pc_name, const utils::String& datetime_clustered);
  Cluster(const utils::String& path);

  const utils::String& GetClusterName() const;
  const utils::String& GetPCName() const;
  const utils::String& GetDateTimeClustered() const;

  void SaveTo(const utils::String& path) const;

private:
  void LoadFrom(const utils::String& path);

private:
  utils::String m_cluster_name;
  utils::String m_pc_name;
  utils::String m_datetime_clustered;
};
#endif // CLUSTER_H
