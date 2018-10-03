#ifndef __STATISTICSMANAGER__
#define __STATISTICSMANAGER__

#include "utils/containers/vector.h"
#include "utils/threads/thread.h"
#include "utils/containers/string.h"

#include "Model/Measurement/MeasurementTool.h"
#include "Model/Common/ValueStamp.h"

class StatisticsManager
{
public:
  StatisticsManager();
  void StartMeasurement();
  void StopMeasurement();
  void SaveMeasurementData(const utils::String& path);
private:
  utils::Vector<utils::UniquePtr<MeasurementTool> > m_measurement_tools;
  utils::Vector<utils::threads::Thread> m_measurement_threads;
  utils::String m_last_start;
};

#endif // __STATISTICSMANAGER__
