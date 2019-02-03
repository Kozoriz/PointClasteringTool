#include "cloperunner.hpp"
#include "ui_cloperunner.h"

CREATE_LOGGER("ClopeRunner");

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
  LOG_DEBUG("value : "<< ui->doubleSpinBox->value());
  m_controller.RunClistring(m_cloud.toStdString(), "CLOPE", {{"sensitivity", ui->doubleSpinBox->value()}});
  this->hide();
}

void ClopeRunner::on_ClopeRunner_destroyed()
{
}
