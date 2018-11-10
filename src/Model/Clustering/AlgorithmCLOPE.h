#pragma once

#include "Model/Clustering/ClusteringAlgo.h"

class AlgorithmCLOPE : public ClusteringAlgo
{
public:
   virtual ~AlgorithmCLOPE();
   utils::Vector<utils::SharedPtr<Cluster> > RunTask(const PointCloud& pc) override;
   utils::String GetName() const override;


private:
   Double calculateProfitWithPoint(Cluster& cluster, const Cluster::ContainerType::key_type& new_point, bool save_to_cluster = false);

};

