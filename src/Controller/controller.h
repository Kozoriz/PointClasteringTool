#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model/PointCloudManager/PointCloudManager.h"
#include "UI/IRender.hpp"
#include <map>

#include "Model/Settings/applicationsettings.h"

class Controller
{
public:
  Controller(PointCloudManager& pc_manager, std::shared_ptr<IRender>&);

  void fillCloudList() const;

  void newFileOpened(utils::String& filename);
  void cloudChoosen(utils::String& filename);

  void RunClistring(const utils::String &sPCName, const utils::String &sAlgo, std::map<utils::String, double> params);
  void AddCloudToList(utils::String name);
  void AddCluster(const utils::String& sPCname, const utils::String& clusterName);

private:
  PointCloudManager& m_pc_manager;
  std::shared_ptr<IRender>& m_render;
};

#endif // CONTROLLER_H
