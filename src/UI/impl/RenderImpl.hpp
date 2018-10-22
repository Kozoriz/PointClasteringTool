#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <memory>

#include "QtRenderObject.hpp"
#include "../Render.hpp"

class RenderImpl : public Render
{
public:
    RenderImpl();
    void start_app( ) override;
    void setController(Controller* controller) override;
    void newFileOpened(utils::String filename) override;

private:
    QQmlApplicationEngine engine;
    QtRedebleOject m_ui_wrapper;
    Controller* m_controller;
};
