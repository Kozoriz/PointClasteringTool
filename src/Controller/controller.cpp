#include "controller.h"
#include "utils/logger.h"

CREATE_LOGGER("Controller")

Controller::Controller(PointCloudManager& pc_manager, std::shared_ptr<Render>& qml_wrapper)
  : m_pc_manager(pc_manager)
  , m_qml_wrapper(qml_wrapper)
{
  LOG_AUTO_TRACE();
}

void Controller::fillCloudList() const
{
  LOG_AUTO_TRACE();
  utils::Vector<utils::String> names = m_pc_manager.GetCloudNames();
  for(auto name : names)
  {
    m_qml_wrapper->addCloudToList(name);
  }
}

void Controller::newFileOpened(utils::String &filename)
{
  LOG_TRACE("File choosen " << filename);

  SharedPtr<PointCloud> pc = m_pc_manager.LoadNewCloud(filename);
  m_qml_wrapper->addCloudToList(pc->GetPCName());
  m_pc_manager.RunClasteringProcess(pc);
}

void Controller::cloudChoosen(utils::String &filename)
{
  LOG_AUTO_TRACE();
  const PointCloud& cloud = m_pc_manager.GetMatrix(filename);
  for(auto& point : cloud)
  {
    m_qml_wrapper->addPoint(point);
  }

//  test for performance of renderer
//  for(int i = 0; i < 1000000; ++i)
//  {
//    m_qml_wrapper->addPoint({rand(), rand(), rand()});
//  }
}
