#include "UIWindow.hpp"

#include "ui_vtkwindow.h"

#include <QtDebug>
#include <QFileDialog>

#include "utils/logger.h"
CREATE_LOGGER("UI")

UIWindow::UIWindow(Controller &con, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::UIWindow),
    m_controller(con),
    clope_w(con, this),
    mst_w(con, this)
{
    ui->setupUi(this);

    // Set up the QVTK window
    viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false));
    ui->qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
    viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());
//    viewer->setBackgroundColor(10,10,10);
    ui->qvtkWidget->update ();

    connect(ui->file, SIGNAL(triggered()), this, SLOT(openFileDialog()));
    connect(ui->listCloud, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(cloudChoosen(QListWidgetItem*)));
    connect(ui->actionCLOPE, SIGNAL(triggered()), this, SLOT(openCLOPERunner()));
    connect(ui->actionMST, SIGNAL(triggered()), this, SLOT(openMSTRunner()));
}

UIWindow::~UIWindow()
{
    delete ui;
}

void UIWindow::addCloudToList(const utils::String &name)
{
    ui->listCloud->addItem(QString(name.c_str()));
}


void UIWindow::showCloud(PointCloud::ConstPtr pc)
{
//  viewer->removePointCloud();
  if(!viewer->updatePointCloud<PointCloud::PointType>(pc))
  {
    viewer->addPointCloud<PointCloud::PointType>(pc);
  }
  viewer->resetCamera ();
  ui->qvtkWidget->update ();
}

void UIWindow::openFileDialog( )
{
    QString fileName = QFileDialog::getOpenFileName(this);

    if(fileName.isEmpty())
    {
        LOG_ERROR("Could not open file.");
        return;
    }

    utils::String fileNameString(fileName.toStdString());
    m_controller.newFileOpened(fileNameString);
}

void UIWindow::cloudChoosen(QListWidgetItem* item)
{
    utils::String str(item->text().toStdString());
    m_controller.cloudChoosen(str);
}

void UIWindow::openCLOPERunner()
{
  clope_w.show();
}

void UIWindow::openMSTRunner()
{
  mst_w.show();

}
