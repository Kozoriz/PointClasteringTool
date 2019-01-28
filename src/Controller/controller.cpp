#include "controller.h"
#include "utils/logger.h"

CREATE_LOGGER("Controller")

Controller::Controller(PointCloudManager& pc_manager, std::shared_ptr<IRender>& render)
  : m_pc_manager(pc_manager)
  , m_render(render)
{
  LOG_AUTO_TRACE();
}

void Controller::fillCloudList() const
{
  LOG_AUTO_TRACE();
  utils::Vector<utils::String> names = m_pc_manager.GetCloudNames();
  for(auto name : names)
  {
    m_render->addCloudToList(name);
  }
}

void Controller::newFileOpened(utils::String &filename)
{
  LOG_TRACE("File choosen " << filename);

  SharedPtr<PointCloud> pc = m_pc_manager.LoadNewCloud(filename);
  m_render->addCloudToList(pc->GetPCName());
  m_pc_manager.RunClasteringProcess(pc);
}

void Controller::cloudChoosen(utils::String & filename)
{
  LOG_AUTO_TRACE();
  m_render->ShowCloud(m_pc_manager.GetMatrix(filename));
}
