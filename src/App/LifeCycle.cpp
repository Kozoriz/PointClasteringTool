#include "LifeCycle.hpp"

#include "UI/impl/RenderImpl.hpp"

#include <functional>

#include "utils/logger.h"
CREATE_LOGGER("LifeCicle");

LifeCycle::LifeCycle( )
    : m_settings("config.ini")
    , m_stat_manager(m_settings)
    , m_pc_manager(m_settings, m_stat_manager)
    , m_controller(m_pc_manager, m_render)
{
}

void
LifeCycle::init( )
{
    LOG_INFO("Init project");
    m_render.reset( new RenderImpl(m_controller));
    m_pc_manager.SetController(&m_controller);
}

void
LifeCycle::start( )
{
    LOG_INFO( "Start project" );
    m_render->start_app();
    m_controller.fillCloudList();
}

void
LifeCycle::stop( )
{
    LOG_INFO( "Stop project" );
}
