#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "LifeCycle.hpp"

int
main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    LifeCycle lifeCycle;
    lifeCycle.init( );
    lifeCycle.start( );

    app.exec( );

    lifeCycle.stop( );

    return 1;
}
