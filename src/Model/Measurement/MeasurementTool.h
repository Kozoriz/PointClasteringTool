#ifndef __MEASUREMENTTOOL__
#define __MEASUREMENTTOOL__

#include "utils/threads/thread_runnable.h"
#include "utils/containers/vector.h"

#include "Model/Common/ValueStamp.h"

class MeasurementTool : public utils::threads::ThreadRunnable
{
public:
  virtual ~MeasurementTool() = 0;
  virtual inline utils::String GetName() const = 0;
  virtual const utils::Vector<ValueStamp> &GetValues() const;
  virtual void Clear();
  void Join() override;
private:
  utils::Vector<ValueStamp> m_values;
  bool is_joined = false;
};

#endif // __MEASUREMENTTOOL__
