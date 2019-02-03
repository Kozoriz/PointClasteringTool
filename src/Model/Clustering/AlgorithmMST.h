#pragma once

#include "Model/Clustering/ClusteringAlgo.h"
#include "Model/Settings/applicationsettings.h"

class AlgorithmMST : public ClusteringAlgo
{
public:
  AlgorithmMST(const ApplicationSettings& settings);
  virtual ~AlgorithmMST();
  utils::Vector<Cluster> RunTask(PointCloud::Ptr pc) override;
  utils::String GetName() const override;

  void SetParams(std::map<utils::String, double> params) override;

private:
  const ApplicationSettings& m_settings;

  int N_count = 2;
  int C_count = 1;

};
