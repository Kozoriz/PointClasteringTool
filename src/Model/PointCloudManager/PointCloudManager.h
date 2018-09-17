#ifndef __POINTCLOUDMANAGER__
#define __POINTCLOUDMANAGER__

#include <memory>

#include "Model/Statistics/StatisticsManager.h"
#include "Model/Clastering/ClasteringAlgo.h"

class PointCloudManager
{
public:
	virtual ~PointCloudManager() {};


private:
  std::shared_ptr<StatisticsManager> m_stats_manager;
  std::vector<std::unique_ptr<ClasteringAlgo> > m_clastering_algos;
};

#endif // __POINTCLOUDMANAGER__
