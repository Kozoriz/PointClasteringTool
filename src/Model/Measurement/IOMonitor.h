#ifndef __IOMONITOR__
#define __IOMONITOR__

#include "Model/Measurement/MeasurementTool.h"

class IOMonitor : public  MeasurementTool
{
public:
  virtual ~IOMonitor();
  void Run() override;
  void Join() override;
  inline utils::String GetName() const override {return "IO";}
};

#endif // __IOMONITOR__
