#ifndef __POINTCLOUDMANAGER__
#define __POINTCLOUDMANAGER__

#include "utils/pointers/unique_ptr.h"
#include "utils/pointers/shared_prt.h"
#include "utils/containers/vector.h"
#include "utils/containers/string.h"
#include "utils/structures/matrix3.h"

#include "Model/Statistics/StatisticsManager.h"
#include "Model/Clastering/ClasteringAlgo.h"

class PointCloudManager
{
  struct PointCloud
  {
    utils::structures::Matrix3 m_matrix;
    utils::String m_cloud_name;
    bool m_is_clustered;
  };

public:
  virtual ~PointCloudManager() {}
  void LoadNewCloud(utils::String& sPath);
  void RunClasteringProcess(PointCloud& cloud);

private:
  utils::SharedPtr<StatisticsManager> m_stats_manager;
  utils::Vector<utils::UniquePtr<ClasteringAlgo> > m_clastering_algos;
  utils::Vector<PointCloud> m_point_clouds;
  utils::Vector<PointCloud> m_clasters;
};

#endif // __POINTCLOUDMANAGER__
