#pragma once

#include <memory>
#include <thread>

#include "../Common/helper/app_helper.hpp"
#include "../Common/helper/communications.hpp"
#include "../DataMeneger/DataMeneger.hpp"
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
    DataMeneger dataMeneger;
    Render render;

    common::Communications< bool, bool, DataMeneger > create_cloude_signal;
};
