#ifndef MSTRUNNER_H
#define MSTRUNNER_H

#include <QDialog>
#include "Controller/controller.h"

namespace Ui {
class MSTRunner;
}

class MSTRunner : public QDialog
{
  Q_OBJECT

public:
  MSTRunner(Controller& controller, QWidget *parent = nullptr);
  ~MSTRunner();

private slots:
  void on_MSTRunner_destroyed();

  void on_pushButton_clicked();

private:
  Ui::MSTRunner *ui;
  Controller& m_controller;
};

#endif // MSTRUNNER_H
