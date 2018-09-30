#include "DataManager.hpp"

#include "impl/DataManagerImpl.hpp"
#include "../Common/app_type/Point.hpp"

#include "utils/logger.h"

CREATE_LOGGER("DataManager");

DataManager::DataManager( )
{
    LOG_INFO( "Create DataManager" );
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
