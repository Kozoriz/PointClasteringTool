#ifndef __STATISTICSMANAGER__
#define __STATISTICSMANAGER__

#include "utils/containers/vector.h"
#include "utils/pointers/unique_ptr.h"
#include "utils/containers/string.h"

#include "Model/Measurement/MeasurementTool.h"
#include "Model/Common/ValueStamp.h"

class StatisticsManager
{
public:
  virtual ~StatisticsManager() {}
  void StartMeasurement();
  void StopMeasurement();
  void SaveMeasurementData(const utils::String& path);
  //utils::Vector<ValueStamp>& values
private:
 utils::Vector<utils::UniquePtr<MeasurementTool> > m_measuremenjt_tools;
};

#endif // __STATISTICSMANAGER__
