#pragma once

#include "utils/containers/string.h"

class Controller;

class Render
{
public:
  virtual ~Render(){}
  virtual void start_app( ) = 0;
  virtual void setController(Controller* c) = 0;
  virtual void newFileOpened(utils::String filename) = 0;
};
