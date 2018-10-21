#include "RAMMonitor.h"

#include "utils/threads/synchronization/conditional_variable.h"
#include "utils/logger.h"

CREATE_LOGGER("RAMMonitor");

RAMMonitor::~RAMMonitor() {}

void RAMMonitor::Run()
{
  LOG_AUTO_TRACE();
  FILE* file = fopen("/proc/self/status", "r");

  utils::synchronization::ConditionalVariable cv;
  utils::synchronization::Lock l;
  while(!is_joined)
  {
    char line[128];
    fseek(file, 0, SEEK_SET);

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
          int i = strlen(line);
          const char* p = line;
          while (*p <'0' || *p > '9') p++;
          line[i-3] = '\0';
          double value = static_cast<double>(atoi(p));
          m_values.push_back({value,utils::date_time::GetTimeStamp()});
          LOG_TRACE("Loop " << value);
          break;
        }
    }
    cv.WaitFor(l, 100); // TODO use app settings
  }
  fclose(file);
}
