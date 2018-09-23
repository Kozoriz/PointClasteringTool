#ifndef CLUSTER_H
#define CLUSTER_H

#include "utils/structures/matrix3.h"

class Cluster : public utils::structures::Matrix3
{
public:
  Cluster(const utils::String& cluster_name, const utils::String& pc_name, const utils::String& datetime_clustered);

  const utils::String& GetClusterName() const;
  const utils::String& GetPCName() const;
  const utils::String& GetDateTimeClustered() const;
private:
  const utils::String m_cluster_name;
  const utils::String& m_pc_name;
  const utils::String m_datetime_clustered;
};
#endif // CLUSTER_H
