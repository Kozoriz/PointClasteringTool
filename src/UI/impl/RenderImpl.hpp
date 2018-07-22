#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <memory>

#include "../Common/helper/communications.hpp"
#include "QtRenderObject.hpp"

class RenderImpl
{
public:
    RenderImpl(common::CommunicationsWithDataMeneger& dm);
    void start_app( );

private:
    QQmlApplicationEngine engine;
    std::unique_ptr<QtRedebleOject> redebleOject;

    common::CommunicationsWithDataMeneger& cm_with_dm;
};
