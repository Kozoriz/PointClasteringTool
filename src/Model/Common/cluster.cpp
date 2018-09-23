#include "cluster.h"

Cluster::Cluster(const utils::String &cluster_name, const utils::String &pc_name, const utils::String &datetime_clustered)
  : m_cluster_name(cluster_name)
  , m_pc_name(pc_name)
  , m_datetime_clustered(datetime_clustered){}

const utils::String &Cluster::GetClusterName() const
{
  return m_cluster_name;
}

const utils::String &Cluster::GetPCName() const
{
  return m_pc_name;
}

const utils::String &Cluster::GetDateTimeClustered() const
{
  return m_datetime_clustered;
}
