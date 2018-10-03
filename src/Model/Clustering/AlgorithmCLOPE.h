#pragma once

#include "Model/Clustering/ClusteringAlgo.h"

class AlgorithmCLOPE : public ClusteringAlgo
{
public:
  ~AlgorithmCLOPE() override;
   utils::Vector<utils::SharedPtr<Cluster> > RunTask(const PointCloud& pc) override;
   utils::String GetName() const override;
};

