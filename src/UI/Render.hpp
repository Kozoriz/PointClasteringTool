#pragma once

#include "utils/containers/string.h"
#include "Model/Common/pointcloud.h"

class Controller;

class Render
{
public:
  virtual ~Render(){}
  virtual void start_app( ) = 0;
  virtual void setController(Controller* c) = 0;
  virtual void newFileOpened(utils::String filename) = 0;
  virtual void cloudChoosen(utils::String cloudpath) = 0;
  virtual void addPoint(const PointCloud::PointType& point) = 0;
  virtual void addCloudToList(const utils::String& name) = 0;
};
