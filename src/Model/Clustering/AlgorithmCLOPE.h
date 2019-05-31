#pragma once

#include "Model/Clustering/ClusteringAlgo.h"
#include "Model/Settings/applicationsettings.h"

class AlgorithmCLOPE : public ClusteringAlgo
{
public:
   AlgorithmCLOPE(const ApplicationSettings& settings);
   virtual ~AlgorithmCLOPE();
   utils::Vector<Cluster> RunTask(PointCloud::Ptr pc) override;
   utils::String GetName() const override;


   void SetParams(std::map<utils::String, double> params) override;
private:
//   Double calculateProfitWithPoint(Cluster& cluster, const Cluster::ContainerType::key_type& new_point, bool save_to_cluster = false);
   const ApplicationSettings& m_settings;

   double sensivity = 0.5;
};

