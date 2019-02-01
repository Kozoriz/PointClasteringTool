#include "cloperunner.hpp"
#include "ui_cloperunner.h"

ClopeRunner::ClopeRunner(Controller& controller, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ClopeRunner),
  m_controller(controller)
{
  ui->setupUi(this);
}

ClopeRunner::~ClopeRunner()
{
  delete ui;
}

void ClopeRunner::on_pushButton_clicked()
{
  this->hide();
}

void ClopeRunner::on_ClopeRunner_destroyed()
{
}
