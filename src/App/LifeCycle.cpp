#include "LifeCycle.hpp"

#include "../Common/helper/app_helper.hpp"
#include "../DataMeneger/impl/DataMenegerImpl.hpp"
#include "../RenderCloude/impl/RenderImpl.hpp"

#include <boost/log/trivial.hpp>
#include <functional>

LifeCycle::LifeCycle( )
    : dataMeneger( )
    , render( )
{
}

void
LifeCycle::init( )
{
    BOOST_LOG_TRIVIAL( trace ) << "Init project";
    common::AppointeeImpl::appointee< Render >( render, std::make_shared< RenderImpl >( ) );
    common::AppointeeImpl::appointee< DataMeneger >( dataMeneger,
                                                     std::make_shared< DataMenegerImpl >( ) );
}

void
LifeCycle::start( )
{
    BOOST_LOG_TRIVIAL( trace ) << "Start project";

    render.start_app( );
}

void
LifeCycle::stop( )
{
    BOOST_LOG_TRIVIAL( trace ) << "Stop project";
}
