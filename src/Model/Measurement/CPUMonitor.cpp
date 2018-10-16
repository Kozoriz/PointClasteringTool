#include "CPUMonitor.h"
#include "utils/threads/synchronization/conditional_variable.h"


#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/times.h"
#include "sys/vtimes.h"

CPUMonitor::~CPUMonitor() {}

void CPUMonitor::Run()
{
  clock_t lastCPU, lastSysCPU, lastUserCPU;
  int numProcessors;

  FILE* file;
  struct tms timeSample;
  char line[128];

  lastCPU = times(&timeSample);
  lastSysCPU = timeSample.tms_stime;
  lastUserCPU = timeSample.tms_utime;

  file = fopen("/proc/cpuinfo", "r");
  numProcessors = 0;
  while(fgets(line, 128, file) != NULL){
      if (strncmp(line, "processor", 9) == 0) numProcessors++;
  }
  fclose(file);


  utils::synchronization::ConditionalVariable cv;
  utils::synchronization::Lock l;
  while(!is_joined)
  {
    struct tms timeSample;
    clock_t now;
    double percent;

    now   = times(&timeSample);
    if (now <= lastCPU || timeSample.tms_stime < lastSysCPU ||
        timeSample.tms_utime < lastUserCPU){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        percent = (timeSample.tms_stime - lastSysCPU) +
            (timeSample.tms_utime - lastUserCPU);
        percent /= (now - lastCPU);
        percent /= numProcessors;
        percent *= 100;
    }
    if(0 < percent) this->m_values.push_back({percent, utils::date_time::GetTimeStamp()});

    lastCPU = now;
    lastSysCPU = timeSample.tms_stime;
    lastUserCPU = timeSample.tms_utime;

    cv.WaitFor(l, 100); // TODO use app settings
  }
}
