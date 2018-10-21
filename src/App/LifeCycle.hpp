#pragma once

#include <memory>
#include <thread>

#include "../Common/helper/app_helper.hpp"
#include "../Common/helper/communications.hpp"
#include "../DataManager/DataManager.hpp"
#include "../UI/Render.hpp"
#include "Model/PointCloudManager/PointCloudManager.h"
#include "Model/Statistics/StatisticsManager.h"
#include "Model/Settings/applicationsettings.h"

class LifeCycle
{
public:
    LifeCycle( );
    void init( );
    void start( );
    void stop( );

private:
    // Module
    DataManager dataMeneger;
    Render render;

    common::CommunicationsWithDataManager cm_with_dm;

    ApplicationSettings m_settings;
    StatisticsManager m_stat_manager;
    PointCloudManager m_pc_manager;
};


