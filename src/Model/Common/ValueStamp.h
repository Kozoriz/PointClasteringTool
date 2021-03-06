#ifndef __VALUESTAMP__
#define __VALUESTAMP__

#include "utils/containers/string.h"
#include "utils/date_time.h"
#include "utils/containers/converters.h"

class ValueStamp
{
public:
  enum class ValueType
  {
    CPU,
    RAM,
    IO_READ,
    IO_WRITE
  };

public:
  utils::String ToString() const { return utils::date_time::GetDateTimeString("%F_%T", m_time) + " " + utils::ConvertToString(m_value); }

public:
  double m_value;
  std::chrono::system_clock::time_point m_time;
};

#endif // __VALUESTAMP__
