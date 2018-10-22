#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model/PointCloudManager/PointCloudManager.h"
#include "UI/Render.hpp"

class Controller
{
public:
  Controller(PointCloudManager& pc_manager, std::shared_ptr<Render>& qml_wrapper);
  void newFileOpened(utils::String& filename);

private:
  PointCloudManager& m_pc_manager;
  std::shared_ptr<Render> m_qml_wrapper;
};

#endif // CONTROLLER_H
