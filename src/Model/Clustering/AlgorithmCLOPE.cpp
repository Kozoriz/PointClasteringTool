#include "AlgorithmCLOPE.h"

AlgorithmCLOPE::~AlgorithmCLOPE() {}

utils::Vector<utils::SharedPtr<Cluster> > AlgorithmCLOPE::RunTask(const PointCloud &pc)
{
  sleep(5);
  return utils::Vector<utils::SharedPtr<Cluster> >();
}

utils::String AlgorithmCLOPE::GetName() const
{
  return "CLOPE";
}
