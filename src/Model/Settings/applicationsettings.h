#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H


#include "utils/app_settings.h"

class ApplicationSettings : public utils::AppSettings
{
public:
  ApplicationSettings(const utils::String& ini_path);
  const utils::String &get_working_dir() const;

private:
  utils::String m_working_dir;
};

#endif // APPLICATIONSETTINGS_H
