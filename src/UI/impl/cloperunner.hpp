#ifndef CLOPERUNNER_H
#define CLOPERUNNER_H

#include <QDialog>

#include "Controller/controller.h"

namespace Ui {
class ClopeRunner;
}

class ClopeRunner : public QDialog
{
  Q_OBJECT

public:
  ClopeRunner(Controller& controller, QWidget *parent = nullptr);
  ~ClopeRunner();

  inline void SetCloud(QString& cloud){m_cloud=cloud;}

private slots:
  void on_pushButton_clicked();

  void on_ClopeRunner_destroyed();

private:
  Ui::ClopeRunner *ui;
  Controller& m_controller;
  QString m_cloud = "";
};

#endif // CLOPERUNNER_H
