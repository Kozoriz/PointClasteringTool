#include "LifeCycle.hpp"

#include "../DataMeneger/impl/DataMenegerImpl.hpp"
#include "../UI/impl/RenderImpl.hpp"

#include <boost/log/trivial.hpp>
#include <functional>

LifeCycle::LifeCycle( )
    : dataMeneger( )
    , render( )
    , cm_with_dm( dataMeneger )
{
}

void
LifeCycle::init( )
{
    BOOST_LOG_TRIVIAL( trace ) << "Init project";
    common::AppointeeImpl::appointee< DataMeneger >( dataMeneger,
                                                     std::make_shared< DataMenegerImpl >( ) );
    common::AppointeeImpl::appointee< Render >( render, std::make_shared< RenderImpl >( cm_with_dm ) );

    cm_with_dm.conections_all();
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
