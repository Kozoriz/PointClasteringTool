#pragma once

// STD
#include <memory>

// Qt
#include <QMainWindow>

// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

// Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

namespace Ui {
class UIWindow;
}

class UIWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit UIWindow(QWidget *parent = nullptr);
    ~UIWindow();

private:
    Ui::UIWindow *ui;

    std::shared_ptr<pcl::visualization::PCLVisualizer> viewer;

    unsigned int red;
    unsigned int green;
    unsigned int blue;
};
