#include "StatisticsManager.h"

#include "Model/Measurement/RAMMonitor.h"
#include "Model/Measurement/CPUMonitor.h"
#include "Model/Measurement/IOMonitor.h"

#include "utils/date_time.h"
#include "utils/file_system.h"

StatisticsManager::StatisticsManager()
{
  m_measurement_tools.push_back(utils::make_unique<RAMMonitor>());
  m_measurement_tools.push_back(utils::make_unique<CPUMonitor>());
  m_measurement_tools.push_back(utils::make_unique<IOMonitor>());

  for(auto& tool : m_measurement_tools)
  {
    m_measurement_threads.push_back({*tool.get()});
  }
}

void StatisticsManager::StartMeasurement()
{
  m_last_start = utils::date_time::GetDateTimeString("");//TODO
  for(auto& tool : m_measurement_tools)
  {
    tool->Clear();
  }
  for(auto& thread : m_measurement_threads)
  {
    thread.StartThread();
  }
}

void StatisticsManager::StopMeasurement()
{
  for(auto& thread : m_measurement_threads)
  {
    thread.JoinThread();
  }
}

void StatisticsManager::SaveMeasurementData(const utils::String &path)
{
  for(auto& tool : m_measurement_tools)
  {
    utils::String filepath = path + m_last_start + "_" + tool->GetName();
    utils::file_system::File file(filepath);
    file.Open(utils::file_system::File::OpenMode::Write);
    if(file.IsOpened())
    {
      const utils::Vector<ValueStamp>& values = tool->GetValues();
      for(auto& value : values)
      {
        file.WriteLine(value.ToString());
      }
      file.Close();
    }
  }
}
