#include "applicationsettings.h"
#include "utils/logger.h"

CREATE_LOGGER("ApplicationSettings")

ApplicationSettings::ApplicationSettings(const utils::String& ini_path)
{
  LOG_AUTO_TRACE();
  AddOption("general.working_dir", m_working_dir);

  ProcessIniFile(ini_path);
}

const utils::String &ApplicationSettings::get_working_dir() const
{
  return m_working_dir;
}
