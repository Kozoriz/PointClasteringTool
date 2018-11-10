#include "UIWindow.hpp"

#include "ui_vtkwindow.h"

UIWindow::UIWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::UIWindow)
{
    ui->setupUi(this);

    viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false));

    // Set up the QVTK window
    viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false));
    ui->qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
    viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());

    PointCloudT::Ptr cloud;

    red   = 128;
    green = 128;
    blue  = 128;

    // Setup the cloud pointer
    cloud.reset (new PointCloudT);
    // The number of points in the cloud
    cloud->points.resize (10000000);

    for (size_t i = 0; i < cloud->points.size (); ++i)
    {
      cloud->points[i].x = 4024 * rand () / (RAND_MAX + 1.0f);
      cloud->points[i].y = 4024 * rand () / (RAND_MAX + 1.0f);
      cloud->points[i].z = 4024 * rand () / (RAND_MAX + 1.0f);

      cloud->points[i].r = red;
      cloud->points[i].g = green;
      cloud->points[i].b = blue;
    }

    // Set the new color
    for (size_t i = 0; i < cloud->size(); i++)
    {
        cloud->points[i].r = 255 *(4024 * rand () / (RAND_MAX + 1.0f));
        cloud->points[i].g = 255 *(4024 * rand () / (RAND_MAX + 1.0f));
        cloud->points[i].b = 255 *(4024 * rand () / (RAND_MAX + 1.0f));
    }
    viewer->addPointCloud (cloud, "cloud");
    viewer->resetCamera ();
    viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "cloud");
    ui->qvtkWidget->update ();
}

UIWindow::~UIWindow()
{
    delete ui;
}
