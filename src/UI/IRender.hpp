#pragma once

#include "utils/containers/string.h"
#include "utils/structures/position.h"
#include "Model/Common/pointcloud.h"

class Controller;

class IRender
{
public:
  virtual ~IRender(){}
  virtual void start_app( ) = 0;
  virtual void addCloudToList(const utils::String& name) = 0;
  virtual void ShowCloud(PointCloud::ConstPtr cloud) = 0;
  virtual void addClusterToCloud(const utils::String& pcname, const utils::String& clustername) = 0;
  virtual void addSubItem(const utils::String& sPCname, const utils::String& measurer_type, const utils::String& stat_filepath) = 0;
};
