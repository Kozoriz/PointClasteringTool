#include "DataManager.hpp"

#include <boost/log/trivial.hpp>

#include "impl/DataManagerImpl.hpp"
#include "../Common/app_type/Point.hpp"

DataManager::DataManager( )
{
    BOOST_LOG_TRIVIAL( trace ) << "Create DataManager";
}

bool DataManager::creatr_cloude()
{
    if ( mImpl )
         return mImpl->create_random_points_clude( );

    return false;
}

void
DataManager::get_cloude( const PointCloud** cloude )
{
    if ( mImpl )
    {
        *cloude = &mImpl->getCloud( );
    }
}
