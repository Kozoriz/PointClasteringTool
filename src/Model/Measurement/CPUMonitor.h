#ifndef __CPUMONITOR__
#define __CPUMONITOR__

#include "Model/Measurement/MeasurementTool.h"

class CPUMonitor : public MeasurementTool
{
public:
  ~CPUMonitor() override;
  void Run() override;
  inline utils::String GetName() const override {return "CPU";}
};

#endif // __CPUMONITOR__
