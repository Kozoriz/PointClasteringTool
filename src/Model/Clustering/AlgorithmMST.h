#pragma once

#include "Model/Clustering/ClusteringAlgo.h"

class AlgorithmMST : public ClusteringAlgo
{
public:
  virtual ~AlgorithmMST();
  utils::Vector<utils::SharedPtr<Cluster> > RunTask(const PointCloud& pc) override;
  utils::String GetName() const override;
};
