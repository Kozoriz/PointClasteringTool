#pragma once

#include <memory>
#include <thread>

#include "../Common/helper/app_helper.hpp"
#include "../Common/helper/communications.hpp"
#include "../DataManager/DataManager.hpp"
#include "../UI/Render.hpp"

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
};


