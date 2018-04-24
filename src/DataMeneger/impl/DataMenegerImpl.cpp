#include "DataMenegerImpl.hpp"

#include <pcl/common/common.h>
#include <pcl/common/projection_matrix.h>
#include <pcl/impl/point_types.hpp>

#include "../../Common/app_type/Point.hpp"

bool
DataMenegerImpl::create_random_points_clude( )
{
    pcl::PointCloud< pcl::PointXYZ > cloud;
    for ( int i = 1; i <= 100; ++i )
    {
        float random = rand( ) % 30 + 1;
        cloud.push_back( pcl::PointXYZ( random, random, random ) );
    }

    for ( const auto& item : cloud )
    {
        common::Point point{item._PointXYZ::x, item._PointXYZ::y, item._PointXYZ::z};
        mCloude.push_back( point );
    }
    return !mCloude.empty( );
}

const std::vector< common::Point >&
DataMenegerImpl::getCloude( ) const
{
    return mCloude;
}
