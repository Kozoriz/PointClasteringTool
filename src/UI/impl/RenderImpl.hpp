#pragma once

#include "UI/Render.hpp"
#include "UI/impl/UIWindow.hpp"

class RenderImpl : public Render
{
public:
    RenderImpl();
    void start_app( ) override;
    void setController(Controller* controller) override;
    void newFileOpened(utils::String filename) override;
    void cloudChoosen(utils::String cloudpath) override;
    void addPoint(const utils::positions::Location3& point) override;
    void addCloudToList(const utils::String& name) override;

private:
    UIWindow m_ui;
    Controller* m_controller;
};
