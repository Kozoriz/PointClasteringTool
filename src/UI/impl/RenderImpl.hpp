#include <QGuiApplication>
#include <QQmlApplicationEngine>

class RenderImpl
{
public:
    RenderImpl( );
    void qml_registration( );
    void start_app( );

private:
    QQmlApplicationEngine engine;
};
