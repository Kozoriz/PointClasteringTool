#ifndef __MEASUREMENTTOOL__
#define __MEASUREMENTTOOL__

#include "utils/threads/thread_runnable.h"
#include "utils/threads/synchronization/atomic.h"
#include "utils/threads/synchronization/barrier.h"
#include "utils/containers/vector.h"

#include "Model/Common/ValueStamp.h"
#include "Model/Settings/applicationsettings.h"

class MeasurementTool : public utils::threads::ThreadRunnable
{
public:
  MeasurementTool(utils::synchronization::Barrier& stop_barrier, ApplicationSettings& settings);
  virtual ~MeasurementTool(){}
  virtual inline utils::String GetName() const = 0;
  virtual const utils::Vector<ValueStamp> &GetValues() const;
  virtual void Clear();
  void Join() override;

protected:
  utils::synchronization::AtomicBool is_joined;
  utils::Vector<ValueStamp> m_values;
  utils::synchronization::Barrier& m_stop_barrier;

   ApplicationSettings& m_settings;
};

#endif // __MEASUREMENTTOOL__
