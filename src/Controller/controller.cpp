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
//  m_pc_manager.RunClasteringProcess(pc);
}

void Controller::AddCloudToList(utils::String name)
{
  m_render->addCloudToList(name);
}

void Controller::AddCluster(const utils::String &sPCname, const utils::String &clusterName)
{
  m_render->addClusterToCloud(sPCname, clusterName);
}

void Controller::AddStatToClustered(const utils::String &sPcName, const utils::String &measurer_type, const utils::String &stat_filepath)
{
  m_render->addSubItem(sPcName, measurer_type, stat_filepath);
}

void Controller::cloudChoosen(utils::String & filename)
{
  LOG_AUTO_TRACE();
  m_render->ShowCloud(m_pc_manager.GetMatrix(filename));
}

void Controller::RunClistring(const utils::String &sPCName, const utils::String &sAlgo, std::map<utils::String, double> params)
{
  for(auto a : params)
  {
    LOG_DEBUG(a.first << " -> " << a.second);
  }
   m_pc_manager.RunClasteringProcess(m_pc_manager.GetMatrix(sPCName), sAlgo, params);
}
