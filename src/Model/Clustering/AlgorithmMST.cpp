#include "AlgorithmMST.h"

AlgorithmMST::~AlgorithmMST() {}

utils::Vector<utils::SharedPtr<Cluster> > AlgorithmMST::RunTask(const PointCloud &pc)
{
  return utils::Vector<utils::SharedPtr<Cluster> >();
}

utils::String AlgorithmMST::GetName() const
{
  return "MST";
}
