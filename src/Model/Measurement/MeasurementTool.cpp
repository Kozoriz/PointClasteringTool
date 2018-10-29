#include "MeasurementTool.h"
#include "utils/logger.h"

CREATE_LOGGER("Measurement")
MeasurementTool::MeasurementTool(utils::synchronization::Barrier& stop_barrier, ApplicationSettings &settings)
  : is_joined(false)
  , m_values()
  , m_stop_barrier(stop_barrier)
  , m_settings(settings)
{
  LOG_AUTO_TRACE();

}

const utils::Vector<ValueStamp> &MeasurementTool::GetValues() const
{
  return m_values;
}

void MeasurementTool::Clear()
{
  LOG_AUTO_TRACE();
  m_values.clear();
}

void MeasurementTool::Join()
{
  LOG_AUTO_TRACE();
  is_joined = true;
}
