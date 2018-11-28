#pragma once

#include "utils/containers/vector.h"
#include "utils/pointers/shared_prt.h"

#include "Model/Common/pointcloud.h"
#include "Model/Common/cluster.h"

class ClusteringAlgo
{
public:
  virtual utils::Vector<Cluster> RunTask(PointCloud::Ptr pc) = 0;
  virtual utils::String GetName() const = 0;
};
