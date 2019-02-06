#include "UIWindow.hpp"

#include "ui_vtkwindow.h"

#include <QtDebug>
#include <QFileDialog>

#include "utils/logger.h"
#include "utils/file_system.h"

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
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5);
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
  viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3);
  viewer->resetCamera ();
  ui->qvtkWidget->update ();
}

QTreeWidgetItem* UIWindow::addSubItem(const utils::String &top, const utils::String &child)
{
  auto items = ui->listCloud->findItems(top.c_str(), Qt::MatchExactly);
  if(0 == items.size())
  {
    LOG_ERROR("child not flound in list " << top);
    return nullptr;
  }
  auto item = items[0];

  QTreeWidgetItem* child_item = new QTreeWidgetItem(item);
  item->addChild(child_item);
  child_item->setText(0, child.c_str());
  return child_item;
}

QTreeWidgetItem* UIWindow::addSubItem(const utils::String &top, const utils::String &child, const utils::String &childchild)
{
  QTreeWidgetItem* child_item = addSubItem(top, child);
  QTreeWidgetItem* child__child_item = new QTreeWidgetItem(child_item);
  child_item->addChild(child__child_item);
  child__child_item->setText(0, childchild.c_str());
  return child__child_item;
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

void UIWindow::openStatFileWindow(QString filepath)
{
  utils::file_system::File file(filepath.toStdString());

  file.Open(utils::file_system::File::OpenMode::Read);

  if(!file.IsOpened())
  {
    LOG_ERROR("Cant open " << file.GetFullPath());
    return;
  }

  std::vector<uint64_t> time;
  std::vector<double> values;

  utils::String line;
  while(!file.IsEof())
  {
    line = file.ReadLine();
    if(line.empty()) continue;

    utils::Vector<utils::String> splited = utils::SplitCSV(line, " ");

    time.push_back(utils::convertTo<uint64_t>( splited[0]));
    values.push_back(utils::convertTo<double>( splited[1]));
  }

  file.Close();


  for(int i = 0; i < time.size(); ++i)
  {
    LOG_DEBUG(time[i] << " : " << values[i]);
  }


  SharedPtr<Diagram> d(new Diagram(this, time, values, filepath));
  diagram_w.push_back(d);

  d->show();
}

void UIWindow::on_listCloud_itemClicked(QTreeWidgetItem *item, int column)
{
  QTreeWidgetItem* parent = item->parent();
  QString parent_text = parent ? parent->text(0) : "___";

  if("CPU" == parent_text || "RAM" == parent_text)
  {
    openStatFileWindow(item->text(0));
    return;
  }


  cloudChoosen(item);
}
