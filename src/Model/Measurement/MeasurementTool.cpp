#include "MeasurementTool.h"

const utils::Vector<ValueStamp> &MeasurementTool::GetValues() const
{
  return m_values;
}

void MeasurementTool::Clear()
{
  m_values.clear();
}
