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

RenderImpl::RenderImpl()
  : m_ui()
{
  LOG_AUTO_TRACE();
}

void
RenderImpl::start_app( )
{
  LOG_AUTO_TRACE();
  m_ui.show();

}

void RenderImpl::setController(Controller* controller)
{
  LOG_AUTO_TRACE();
  m_controller = controller;
}

void RenderImpl::newFileOpened(utils::String filename)
{
  LOG_TRACE(filename);
  m_controller->newFileOpened(filename);
}

void RenderImpl::cloudChoosen(utils::String cloudpath)
{
  LOG_TRACE(cloudpath);
  m_controller->cloudChoosen(cloudpath);
}

void RenderImpl::addPoint(const utils::positions::Location3 &point)
{
  LOG_TRACE(point.ToString());
//  QVector3D qpoint(point.x_, point.y_, point.z_);
//  m_ui_wrapper.addNewPoint(qpoint);
}

void RenderImpl::addCloudToList(const utils::String &name)
{
  LOG_TRACE(name);
//  m_ui_wrapper.addCloudToList(name.c_str());
}
