#include "RenderImpl.hpp"

#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

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
  LOG_TRACE(cloud->GetPCName());
  m_ui.showCloud(cloud);
}
