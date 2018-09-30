#include "LifeCycle.hpp"

#include "../DataManager/impl/DataManagerImpl.hpp"
#include "../UI/impl/RenderImpl.hpp"

#include <functional>

#include "utils/logger.h"

CREATE_LOGGER("LifeCicle");

LifeCycle::LifeCycle( )
    : dataMeneger( )
    , render( )
    , cm_with_dm( dataMeneger )
{
}

void
LifeCycle::init( )
{
    LOG_INFO("Init project");
    common::AppointeeImpl::appointee< DataManager >( dataMeneger,
                                                     std::make_shared< DataManagerImpl >( ) );
    common::AppointeeImpl::appointee< Render >( render, std::make_shared< RenderImpl >( cm_with_dm ) );

    cm_with_dm.conections_all();
}

void
LifeCycle::start( )
{
    LOG_INFO( "Start project" );
    render.start_app( );
}

void
LifeCycle::stop( )
{
    LOG_INFO( "Stop project" );
}
