#pragma once

#include <memory>
#include <thread>

#include "Model/PointCloudManager/PointCloudManager.h"
#include "Model/Statistics/StatisticsManager.h"
#include "Model/Settings/applicationsettings.h"
#include "Controller/controller.h"
#include "UI/IRender.hpp"

class LifeCycle
{
public:
    LifeCycle( );
    void init( );
    void start( );
    void stop( );

private:
    // Module


    ApplicationSettings m_settings;
    StatisticsManager m_stat_manager;
    PointCloudManager m_pc_manager;
    std::shared_ptr<IRender> m_render;
    Controller m_controller;
};


