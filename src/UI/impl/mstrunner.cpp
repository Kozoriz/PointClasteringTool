#include "mstrunner.hpp"
#include "ui_mstrunner.h"

MSTRunner::MSTRunner(Controller& controller, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::MSTRunner),
  m_controller(controller)
{
  ui->setupUi(this);
}

MSTRunner::~MSTRunner()
{
  delete ui;
}



void MSTRunner::on_MSTRunner_destroyed()
{
}

void MSTRunner::on_pushButton_clicked()
{
    this->hide();
}
