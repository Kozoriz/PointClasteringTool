#include "applicationsettings.h"
#include "utils/logger.h"

CREATE_LOGGER("ApplicationSettings")

ApplicationSettings::ApplicationSettings(const utils::String& ini_path)
  : m_working_dir("")
  , m_measurement_delay(0)
{
  LOG_AUTO_TRACE();
  AddOption("general.working_dir", m_working_dir);
  AddOption("measurement.measurement_interval", m_measurement_delay);

  ProcessIniFile(ini_path);
}

const utils::String &ApplicationSettings::get_working_dir() const
{
  return m_working_dir;
}

UInt ApplicationSettings::get_measurement_delay() const
{
  return m_measurement_delay;
}
