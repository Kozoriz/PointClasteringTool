#ifndef __VALUESTAMP__
#define __VALUESTAMP__

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
	virtual ~ValueStamp() {};
};

#endif // __VALUESTAMP__
