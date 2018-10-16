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
  utils::String ToString() const { return utils::date_time::GetDateTimeString("") + " " + utils::ConvertToString(m_value); } // TODO time format

public:
  double m_value;
  UInt32 m_time;
};

#endif // __VALUESTAMP__
