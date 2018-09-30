#include "RenderImpl.hpp"

#include <QQmlContext>

#include <iostream>
#include <vector>
#include <memory>

#include "Model/Common/pointcloud.h"

RenderImpl::RenderImpl(common::CommunicationsWithDataManager& dm)
  : redebleOject(std::make_unique<QtRedebleOject>())
  , cm_with_dm(dm)
{
}

void
RenderImpl::start_app( )
{
  cm_with_dm.create_cloude_signal.talk();

  const PointCloud* test_cn = nullptr;
  cm_with_dm.get_cloude_signal.talk(&test_cn);

  QVariantList list;
  const utils::structures::Matrix3* p_test_cn = test_cn;
  for(const auto& item : *p_test_cn )
  {
      QVector3D temp;
      temp.setX(item.x_);
      temp.setY(item.y_);
      temp.setZ(item.z_);
      list << temp;
  }

  engine.rootContext()->setContextProperty("RedebleOject", redebleOject.get());

  redebleOject->setCloude(list);

  engine.load( QUrl( QStringLiteral( "../../UI/impl/Resources/main.qml" ) ) );
}
