#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H


#include "utils/app_settings.h"
#include "utils/numbers.h"

class ApplicationSettings : public utils::AppSettings
{
public:
  ApplicationSettings(const utils::String& ini_path);
  const utils::String &get_working_dir() const;
  UInt get_measurement_delay() const;
  float get_clope_sensivity() const;
  int get_mst_neighbors() const;
  int get_mst_clusters_count() const;

private:
  utils::String m_working_dir;
  UInt m_measurement_delay;
  float m_clope_sensivity;
  int m_mst_neighbors;
  int m_mst_clusters_count;
};

#endif // APPLICATIONSETTINGS_H
