#ifndef __STATISTICSMANAGER__
#define __STATISTICSMANAGER__

#include "utils/containers/string.h"
#include "utils/containers/vector.h"
#include "utils/threads/thread.h"
#include "utils/threads/synchronization/barrier.h"

#include "Model/Measurement/MeasurementTool.h"
#include "Model/Common/ValueStamp.h"
#include "Model/Settings/applicationsettings.h"

class StatisticsManager
{
public:
  StatisticsManager(ApplicationSettings& settings);
  void StartMeasurement();
  void StopMeasurement();
  std::map<utils::String, utils::String> SaveMeasurementData(const utils::String& path);

  utils::String GetLastStart() const {return m_last_start;}
private:
  utils::Vector<utils::UniquePtr<MeasurementTool> > m_measurement_tools;
  utils::Vector<utils::threads::Thread> m_measurement_threads;
  utils::String m_last_start;
  utils::synchronization::Barrier m_tools_stop_barrier;

  ApplicationSettings& m_settings;
};

#endif // __STATISTICSMANAGER__
