#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model/PointCloudManager/PointCloudManager.h"
#include "UI/IRender.hpp"

class Controller
{
public:
  Controller(PointCloudManager& pc_manager, std::shared_ptr<IRender>&);

  void fillCloudList() const;

  void newFileOpened(utils::String& filename);
  void cloudChoosen(utils::String& filename);


private:
  PointCloudManager& m_pc_manager;
  std::shared_ptr<IRender>& m_render;
};

#endif // CONTROLLER_H
