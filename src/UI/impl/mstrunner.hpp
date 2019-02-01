#ifndef MSTRUNNER_H
#define MSTRUNNER_H

#include <QDockWidget>
#include "Controller/controller.h"

namespace Ui {
class MSTRunner;
}

class MSTRunner : public QWidget
{
  Q_OBJECT

public:
  explicit MSTRunner(Controller& controller, QWidget *parent = nullptr);
  ~MSTRunner();

private:
  Ui::MSTRunner *ui;
  Controller& m_controller;
};

#endif // MSTRUNNER_H
