#include "DataMeneger.hpp"

#include <boost/log/trivial.hpp>

#include "impl/DataMenegerImpl.hpp"
#include "../Common/app_type/Point.hpp"

DataMeneger::DataMeneger( )
{
    BOOST_LOG_TRIVIAL( trace ) << "Create DataMeneger";
}

bool DataMeneger::creatr_cloude()
{
    if ( mImpl )
         return mImpl->create_random_points_clude( );

    return false;
}

void
DataMeneger::get_cloude( common::Points& cloude )
{
    if ( mImpl )
    {
        cloude = mImpl->getCloude( );
    }
}
