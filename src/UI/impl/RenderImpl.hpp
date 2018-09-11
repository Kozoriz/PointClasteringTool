#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <memory>

#include "Common/helper/communications.hpp"
#include "QtRenderObject.hpp"

class RenderImpl
{
public:
    RenderImpl(common::CommunicationsWithDataManager& dm);
    void start_app( );

private:
    QQmlApplicationEngine engine;
    std::unique_ptr<QtRedebleOject> redebleOject;

    common::CommunicationsWithDataManager& cm_with_dm;
};
