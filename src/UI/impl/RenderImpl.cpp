#include "RenderImpl.hpp"


#include <iostream>
#include <vector>
#include <memory>

#include "Model/Common/pointcloud.h"
#include "Controller/controller.h"

#include "utils/logger.h"

CREATE_LOGGER("UI")

RenderImpl::RenderImpl(Controller &controller)
    : m_ui(controller)
{
    LOG_AUTO_TRACE();
}

void
RenderImpl::start_app( )
{
  LOG_AUTO_TRACE();
  m_ui.show();

}

void RenderImpl::addCloudToList(const utils::String &name)
{
  LOG_TRACE(name);
  m_ui.addCloudToList(name);
}

void RenderImpl::ShowCloud(PointCloud::ConstPtr cloud)
{
  if(!cloud.get())
  {
    LOG_ERROR("Invalid cloud");
    return;
  }
  LOG_TRACE(cloud->GetPCName());
  m_ui.showCloud(cloud);
}

void RenderImpl::addClusterToCloud(const utils::String &pcname, const utils::String &clustername)
{
  LOG_TRACE(pcname << " : " << clustername);
  m_ui.addSubItem(pcname, clustername);

}

void RenderImpl::addSubItem(const utils::String &sPCname, const utils::String &measurer_type, const utils::String &stat_filepath)
{
  LOG_TRACE(sPCname << " : " << measurer_type << " : " << stat_filepath);
   m_ui.addSubItem(sPCname, measurer_type, stat_filepath);
}
