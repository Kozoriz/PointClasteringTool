#ifndef __STATISTICSMANAGER__
#define __STATISTICSMANAGER__

#include <vector>
#include <memory>

#include "Model/Measurement/MeasurementTool.h"

class StatisticsManager
{
public:
	virtual ~StatisticsManager() {};

private:
  std::vector<std::unique_ptr<MeasurementTool> > m_measuremenjt_tools;
};

#endif // __STATISTICSMANAGER__
