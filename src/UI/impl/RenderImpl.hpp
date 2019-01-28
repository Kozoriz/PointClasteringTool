#pragma once

#include <memory>

#include "UI/IRender.hpp"
#include "UI/impl/UIWindow.hpp"

class RenderImpl : public IRender
{
public:
    RenderImpl(Controller&);

    void start_app( ) override;
    void addCloudToList(const utils::String& name) override;
    void ShowCloud(PointCloud::ConstPtr cloud) override;

private:
    UIWindow m_ui;
};
