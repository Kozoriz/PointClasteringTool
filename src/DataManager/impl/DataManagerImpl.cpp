#include "DataManagerImpl.hpp"

DataManagerImpl::DataManagerImpl()
  : mCloude("test")
{

}

bool DataManagerImpl::create_random_points_clude( )
{
    mCloude.clear();
    for ( int i = 1; i <= 100; ++i )
    {
        float random_x = rand( ) % 30 + 1;
        float random_y = rand( ) % 30 + 1;
        float random_z = rand( ) % 30 + 1;
//        mCloude.AddPoint(random_x, random_y, random_z );
    }

    return 0 != mCloude.size();
}

const PointCloud& DataManagerImpl::getCloud( ) const
{
    return mCloude;
}
