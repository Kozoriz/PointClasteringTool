#pragma once

#include "utils/containers/string.h"
#include "utils/structures/position.h"

class Controller;

class IRender
{
public:
  virtual ~IRender(){}
  virtual void start_app( ) = 0;
  virtual void addCloudToList(const utils::String& name) = 0;
};
