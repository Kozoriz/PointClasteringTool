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
    clope_w(new ClopeRunner(con, this)),
    mst_w(new MSTRunner(con, this))
{
    ui->setupUi(this);

    // Set up the QVTK window
    viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false));
    ui->qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
    viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());
//    viewer->setBackgroundColor(10,10,10);
    ui->qvtkWidget->update ();

    connect(ui->file, SIGNAL(triggered()), this, SLOT(openFileDialog()));
//    connect(ui->listCloud, SIGNAL(itemClicked(QTreeWidgetItem*)), this, SLOT(cloudChoosen(QTreeWidgetItem*)));
    connect(ui->actionCLOPE, SIGNAL(triggered()), this, SLOT(openCLOPERunner()));
    connect(ui->actionMST, SIGNAL(triggered()), this, SLOT(openMSTRunner()));
}

UIWindow::~UIWindow()
{
    delete ui;
}

void UIWindow::addCloudToList(const utils::String &name)
{
  QTreeWidgetItem* item = new QTreeWidgetItem(ui->listCloud);
  item->setText(0, name.c_str());
  ui->listCloud->addTopLevelItem(item);
}


void UIWindow::showCloud(PointCloud::ConstPtr pc)
{
  viewer->removePointCloud();
  if(!viewer->updatePointCloud<PointCloud::PointType>(pc))
  {
    viewer->addPointCloud<PointCloud::PointType>(pc);
  }
  viewer->resetCamera ();
  ui->qvtkWidget->update ();
}

void UIWindow::addClusterToCloud(const utils::String &pcname, const utils::String &clustername)
{
}

void UIWindow::openFileDialog( )
{
    QString fileName = QFileDialog::getOpenFileName(this, "", "/home/andrii/workspace/point_clouds");

    if(fileName.isEmpty())
    {
        LOG_ERROR("Could not open file.");
        return;
    }

    utils::String fileNameString(fileName.toStdString());
    m_controller.newFileOpened(fileNameString);
}

void UIWindow::cloudChoosen(QTreeWidgetItem* item)
{
    utils::String str(item->text(0).toStdString());
    m_last_choosen_cloud = item->text(0);

    LOG_DEBUG("m_last_choosen_cloud = " << m_last_choosen_cloud.toStdString());
    m_controller.cloudChoosen(str);
    ui->menuClustering->setEnabled(true);
}

void UIWindow::openCLOPERunner()
{
//  clope_w->resize(100,100);
  clope_w->SetCloud(m_last_choosen_cloud);
  clope_w->show();
//  this->hide();
}

void UIWindow::openMSTRunner()
{
  mst_w->SetCloud(m_last_choosen_cloud);
//  mst_w->resize(100,100);
  mst_w->show();
//  this->hide();

}

void UIWindow::on_listCloud_itemClicked(QTreeWidgetItem *item, int column)
{
  cloudChoosen(item);
}
