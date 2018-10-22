#include "controller.h"
#include "utils/logger.h"

CREATE_LOGGER("Controller")

Controller::Controller(PointCloudManager& pc_manager, std::shared_ptr<Render>& qml_wrapper)
  : m_pc_manager(pc_manager)
  , m_qml_wrapper(qml_wrapper)
{
  LOG_AUTO_TRACE();
}

void Controller::newFileOpened(utils::String &filename)
{
  LOG_AUTO_TRACE();
  LOG_DEBUG("File choosen " << filename);
  m_pc_manager.RunClasteringProcess(m_pc_manager.LoadNewCloud(filename));
}
