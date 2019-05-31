#include "diagram.h"
#include "ui_diagram.h"

#include <QtCharts/qstackedbarseries.h>
#include <QtCharts/qbarset.h>
#include <QtCharts/qbarcategoryaxis.h>
#include <QtCharts/qlineseries.h>

Diagram::Diagram(QWidget *parent, std::vector<uint64_t> time, std::vector<double> values, const QString title) :
  QDialog(parent),
  ui(new Ui::Diagram)
{
  using namespace QtCharts;

  ui->setupUi(this);
  ui->label->setText(title);

      QLineSeries* ls = new QLineSeries;
      for(int i = 0; i < values.size(); ++i)
      {
        ls->append(i * 100, values[i]);
      }

      QChart *chart = new QChart();
      chart->addSeries(ls);
      chart->setTitle(title);
      chart->setAnimationOptions(QChart::SeriesAnimations);

      QStringList categories;

      for(auto v : time)
      {
        categories << std::to_string(v).c_str();
      }

      QBarCategoryAxis *axis = new QBarCategoryAxis();
//      axis->append(categories);
      axis->setTitleText("Time");
      chart->setAxisX(axis);
      chart->createDefaultAxes();

      QChartView *chartView = new QChartView(chart, ui->verticalLayoutWidget);
      chartView->setRenderHint(QPainter::Antialiasing);
      chartView->resize(640,480);
}

Diagram::~Diagram()
{
  delete ui;
}
