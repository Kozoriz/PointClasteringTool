#include "DataManagerImpl.hpp"

#include <pcl/common/common.h>

#include "../Common/converters/converters_pcl.hpp"

bool
DataManagerImpl::create_random_points_clude( )
{
    pcl::PointCloud< pcl::PointXYZ > cloud;
    for ( int i = 1; i <= 100; ++i )
    {
        float random_x = rand( ) % 30 + 1;
        float random_y = rand( ) % 30 + 1;
        float random_z = rand( ) % 30 + 1;
        cloud.push_back( pcl::PointXYZ( random_x, random_y, random_z ) );
    }

    mCloude = converters::to_common(cloud);

    return !mCloude.empty( );
}

const common::Points&
DataManagerImpl::getCloude( ) const
{
    return mCloude;
}
