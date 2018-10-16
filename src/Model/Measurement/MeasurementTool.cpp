#include "MeasurementTool.h"

MeasurementTool::MeasurementTool()
  : is_joined(false)
{

}

const utils::Vector<ValueStamp> &MeasurementTool::GetValues() const
{
  return m_values;
}

void MeasurementTool::Clear()
{
  m_values.clear();
}

void MeasurementTool::Join()
{
  is_joined = true;
}
