#include "MeasurementTool.h"
#include "utils/logger.h"

CREATE_LOGGER("Measurement")
MeasurementTool::MeasurementTool()
  : is_joined(false)
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
