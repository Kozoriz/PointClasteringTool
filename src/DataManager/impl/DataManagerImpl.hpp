#pragma once

#include <vector>

#include "Model/Common/pointcloud.h"

class DataManagerImpl
{
public:
    DataManagerImpl( );
    bool create_random_points_clude( );
    const PointCloud &getCloud( ) const;

private:
    PointCloud mCloude;
};
