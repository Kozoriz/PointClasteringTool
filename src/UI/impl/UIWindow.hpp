#pragma once

// STD
#include <memory>

// Qt
#include <QMainWindow>
#include <QString>
#include <QListWidget>

// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

// Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>

// Project
#include "Controller/controller.h"

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

namespace Ui {
class UIWindow;
}

class UIWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit UIWindow(Controller&, QWidget *parent = nullptr);
    ~UIWindow();

    void addCloudToList(const utils::String& name);
    void showCloud(PointCloud::ConstPtr pc);


private slots:
    void openFileDialog();
    void cloudChoosen( QListWidgetItem* );

private:
    Ui::UIWindow *ui;
    std::unique_ptr<pcl::visualization::PCLVisualizer> viewer;
    Controller& m_controller;
};
