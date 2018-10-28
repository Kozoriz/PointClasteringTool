#include "RenderImpl.hpp"

#include <QQmlContext>

#include <iostream>
#include <vector>
#include <memory>

#include "Model/Common/pointcloud.h"
#include "Controller/controller.h"

#include "utils/logger.h"

CREATE_LOGGER("UI")

RenderImpl::RenderImpl()
  : engine()
  , m_ui_wrapper()
{
  LOG_AUTO_TRACE();
  m_ui_wrapper.setRenderer(this);
}

void
RenderImpl::start_app( )
{
  LOG_AUTO_TRACE();
//  cm_with_dm.create_cloude_signal.talk();

//  const PointCloud* test_cn = nullptr;
////  cm_with_dm.get_cloude_signal.talk(&test_cn);

//  QVariantList list;
//  const utils::structures::Matrix3* p_test_cn = test_cn;
//  for(const auto& item : *p_test_cn )
//  {
//      QVector3D temp;
//      temp.setX(item.x_);
//      temp.setY(item.y_);
//      temp.setZ(item.z_);
//      list << temp;
//  }

  engine.rootContext()->setContextProperty("Wrapper", &m_ui_wrapper);

  engine.load( QUrl( QStringLiteral( "../../UI/impl/Resources/main.qml" ) ) );
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
  QVector3D qpoint(point.x_, point.y_, point.z_);
  m_ui_wrapper.addNewPoint(qpoint);
}

void RenderImpl::addCloudToList(const utils::String &name)
{
  LOG_TRACE(name);
  m_ui_wrapper.addCloudToList(name.c_str());
}
