#include "RenderImpl.hpp"

#include <QQmlContext>

#include <iostream>
#include <vector>

RenderImpl::RenderImpl(common::CommunicationsWithDataMeneger& dm)
  : redebleOject(std::make_unique<QtRedebleOject>())
  , cm_with_dm(dm)
{
}

void
RenderImpl::start_app( )
{
  cm_with_dm.create_cloude_signal.talk();

  std::vector< common::Point > test_cn;
  cm_with_dm.get_cloude_signal.talk(test_cn);

  QVariantList list;
  for(const auto& item : test_cn )
  {
      QVector3D temp;
      temp.setX(item.x);
      temp.setY(item.y);
      temp.setZ(item.z);
      list << temp;
  }

  engine.rootContext()->setContextProperty("RedebleOject", redebleOject.get());

  redebleOject->setCloude(list);

  engine.load( QUrl( QStringLiteral( "../../UI/impl/Resources/main.qml" ) ) );
}
