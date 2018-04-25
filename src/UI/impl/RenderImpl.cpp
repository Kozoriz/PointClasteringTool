#include "RenderImpl.hpp"

#include "QtRenderObject.hpp"

RenderImpl::RenderImpl( )
{
}

void
RenderImpl::qml_registration( )
{
    qmlRegisterType< QtRedebleOject >( "data_meneger", 1, 0, "DataMeneger" );
}

void
RenderImpl::start_app( )
{
    engine.load( QUrl( QStringLiteral( "../../UI/impl/Resources/main.qml" ) ) );
}
