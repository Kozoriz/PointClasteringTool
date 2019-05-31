#include "StatisticsManager.h"

#include "Model/Measurement/RAMMonitor.h"
#include "Model/Measurement/CPUMonitor.h"
#include "Model/Measurement/IOMonitor.h"

#include "utils/date_time.h"
#include "utils/file_system.h"
#include "utils/logger.h"

CREATE_LOGGER("Statistics")

StatisticsManager::StatisticsManager(ApplicationSettings& settings)
  : m_tools_stop_barrier(0)
  , m_settings(settings)
{
  LOG_AUTO_TRACE();
  m_measurement_tools.push_back(utils::make_unique<RAMMonitor>(m_tools_stop_barrier, settings));
  m_measurement_tools.push_back(utils::make_unique<CPUMonitor>(m_tools_stop_barrier, settings));
//  m_measurement_tools.push_back(utils::make_unique<IOMonitor>());

  for(auto& tool : m_measurement_tools)
  {
    m_measurement_threads.push_back({*tool.get()});
  }
}

void StatisticsManager::StartMeasurement()
{
  LOG_AUTO_TRACE();
  m_last_start = utils::date_time::GetDateTimeString("%F_%T");
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
  LOG_AUTO_TRACE();
  m_tools_stop_barrier.set_count(m_measurement_tools.size() + 1);
  for(auto& tool : m_measurement_tools)
  {
    tool->Join();
  }
  m_tools_stop_barrier.Wait();

  for(auto& thread : m_measurement_threads)
  {
    thread.JoinThread();
  }
}

std::map<utils::String, utils::String> StatisticsManager::SaveMeasurementData(const utils::String &path)
{
  LOG_AUTO_TRACE();
  std::map<utils::String, utils::String> res_mapping;
  for(auto& tool : m_measurement_tools)
  {
    utils::String filepath = utils::file_system::ExtendPath(path, m_last_start + "_" + tool->GetName());
    utils::file_system::Directory::RecursiveCreate(path);

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
    res_mapping[tool->GetName()] = filepath;
  }
  return res_mapping;
}
