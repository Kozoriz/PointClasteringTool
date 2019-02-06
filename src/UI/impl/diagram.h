#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QDialog>
#include <QtCharts/QChartView>

namespace Ui {
class Diagram;
}

class Diagram : public QDialog
{
  Q_OBJECT

public:
  explicit Diagram(QWidget *parent, std::vector<uint64_t> time, std::vector<double> values, const QString title);
  ~Diagram();

private:
  Ui::Diagram *ui;

  QtCharts::QChartView *chartView;

};

#endif // DIAGRAM_H
