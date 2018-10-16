#ifndef __MEASUREMENTTOOL__
#define __MEASUREMENTTOOL__

#include "utils/threads/thread_runnable.h"
#include "utils/threads/synchronization/atomic.h"
#include "utils/containers/vector.h"

#include "Model/Common/ValueStamp.h"

class MeasurementTool : public utils::threads::ThreadRunnable
{
public:
  MeasurementTool();
  virtual ~MeasurementTool() = 0;
  virtual inline utils::String GetName() const = 0;
  virtual const utils::Vector<ValueStamp> &GetValues() const;
  virtual void Clear();
  void Join() override;

protected:
  utils::synchronization::AtomicBool is_joined;
  utils::Vector<ValueStamp> m_values;
};

#endif // __MEASUREMENTTOOL__
