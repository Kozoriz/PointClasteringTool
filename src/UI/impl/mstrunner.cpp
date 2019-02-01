#include "mstrunner.hpp"
#include "ui_mstrunner.h"

MSTRunner::MSTRunner(Controller controller, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MSTRunner),
  m_controller(controller)
{
  ui->setupUi(this);
}

MSTRunner::~MSTRunner()
{
  delete ui;
}


