#include "cloperunner.hpp"
#include "ui_cloperunner.h"

ClopeRunner::ClopeRunner(Controller& controller, QWidget *parent) :
  QWidget(parent),
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

}
