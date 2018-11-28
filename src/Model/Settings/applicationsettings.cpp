#include "applicationsettings.h"
#include "utils/logger.h"

CREATE_LOGGER("ApplicationSettings")

ApplicationSettings::ApplicationSettings(const utils::String& ini_path)
  : m_working_dir("")
  , m_measurement_delay(0)
  , m_clope_sensivity(FLT_MAX)
  , m_mst_neighbors(2)
  , m_mst_clusters_count(1)
{
  LOG_AUTO_TRACE();
  AddOption("general.working_dir", m_working_dir);
  AddOption("measurement.measurement_interval", m_measurement_delay);

  AddOption("clope.sensitivity", m_clope_sensivity);

  AddOption("mst.neighbors_count", m_mst_neighbors);
  AddOption("mst.clusters_count", m_mst_clusters_count);

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

float ApplicationSettings::get_clope_sensivity() const
{
  return m_clope_sensivity;
}

int ApplicationSettings::get_mst_neighbors() const
{
  return m_mst_neighbors;
}

int ApplicationSettings::get_mst_clusters_count() const
{
  return m_mst_clusters_count;
}
