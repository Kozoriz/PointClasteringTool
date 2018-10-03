#ifndef __VALUESTAMP__
#define __VALUESTAMP__

#include "utils/containers/string.h"

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
  utils::String ToString() const { return ""; } // TODO
};

#endif // __VALUESTAMP__
