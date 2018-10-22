#include "LifeCycle.hpp"

#include "../DataManager/impl/DataManagerImpl.hpp"
#include "../UI/impl/RenderImpl.hpp"

#include <functional>

#include "utils/logger.h"

CREATE_LOGGER("LifeCicle");

LifeCycle::LifeCycle( )
    : m_settings("config.ini")
    , m_stat_manager(m_settings)
    , m_pc_manager(m_settings, m_stat_manager)
    , m_qml_wrapper( new RenderImpl() )
    , m_controller(m_pc_manager, m_qml_wrapper)
{
  m_qml_wrapper->setController(&m_controller);
}

void
LifeCycle::init( )
{
    LOG_INFO("Init project");
}

void
LifeCycle::start( )
{
    LOG_INFO( "Start project" );
    m_qml_wrapper->start_app();
}

void
LifeCycle::stop( )
{
    LOG_INFO( "Stop project" );
}
