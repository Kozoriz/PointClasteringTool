#include <QApplication>

#include "utils/logger.h"

#include "LifeCycle.hpp"

#include <clocale>

int
main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    logger::Logger::InitLogger("log4cplus.properties"); // use app settings
    LifeCycle lifeCycle;
    lifeCycle.init( );
    lifeCycle.start( );

    app.exec( );

    lifeCycle.stop( );


    logger::Logger::DeinitLogger();
    return 1;
}
