#ifndef CLOPERUNNER_H
#define CLOPERUNNER_H

#include <QDockWidget>

#include "Controller/controller.h"

namespace Ui {
class ClopeRunner;
}

class ClopeRunner : public QWidget
{
  Q_OBJECT

public:
  ClopeRunner(Controller& controller, QWidget *parent = nullptr);
  ~ClopeRunner();

private slots:
  void on_pushButton_clicked();

private:
  Ui::ClopeRunner *ui;
  Controller& m_controller;
};

#endif // CLOPERUNNER_H
