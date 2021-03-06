#ifndef __CPUMONITOR__
#define __CPUMONITOR__

#include "Model/Measurement/MeasurementTool.h"

class CPUMonitor : public MeasurementTool
{
public:
  CPUMonitor(utils::synchronization::Barrier& stop_barrier, ApplicationSettings &settings);
  virtual ~CPUMonitor();
  void Run() override;
  inline utils::String GetName() const override {return "CPU";}
};

#endif // __CPUMONITOR__
