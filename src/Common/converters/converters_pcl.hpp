#include <pcl/common/common.h>
#include "../Common/app_type/Point.hpp"


namespace converters
{
common::Points to_common( const  pcl::PointCloud< pcl::PointXYZ >& pcl_point_cloude )
{
  common::Points cloude;
  for ( const auto& item : pcl_point_cloude )
  {
      common::Point point{item._PointXYZ::x, item._PointXYZ::y, item._PointXYZ::z};
      cloude.push_back( point );
  }
  return cloude;
}

 pcl::PointCloud< pcl::PointXYZ > to_pcl( const common::Points& common_cloude )
{
   pcl::PointCloud< pcl::PointXYZ > cloude;
  for ( const auto& item : common_cloude )
  {
      pcl::PointXYZ point;
      point._PointXYZ::x = item.x;
      point._PointXYZ::y = item.y;
      point._PointXYZ::z = item.z;
      cloude.push_back( point );
  }
  return cloude;
}

}
