#pragma once

#include "../Common/helper/communications.hpp"
#include "../DataMeneger/DataMeneger.hpp"

class ServiceCommunicationDataMeneger
{
public:
    ServiceCommunicationDataMeneger( const ServiceCommunicationDataMeneger& ) = default;
    ServiceCommunicationDataMeneger( DataMeneger const& dataMeneger )
        : create_cloude_signal( dataMeneger )
    {
        create_cloude_signal.connect( boost::bind( &DataMeneger::creatr_cloude, dataMeneger, _1 ) );
    }

    common::Communications< bool, bool, DataMeneger > create_cloude_signal;
};
