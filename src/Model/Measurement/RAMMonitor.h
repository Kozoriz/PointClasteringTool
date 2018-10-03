#ifndef __RAMMONITOR__
#define __RAMMONITOR__

#include "Model/Measurement/MeasurementTool.h"

class RAMMonitor : public MeasurementTool
{
public:
  ~RAMMonitor() override;
  void Run() override;
  void Join() override;
  inline utils::String GetName() const override {return "RAM";}
};

#endif // __RAMMONITOR__
