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

private:
  const ApplicationSettings& m_settings;
};
