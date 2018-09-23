#pragma once

#include "utils/containers/vector.h"
#include "utils/pointers/shared_prt.h"

#include "Model/Common/pointcloud.h"
#include "Model/Common/cluster.h"

class ClusteringAlgo
{
public:
  virtual ~ClusteringAlgo() {};

  virtual utils::Vector<utils::SharedPtr<Cluster> > RunTask(const PointCloud& pc) = 0;
};
