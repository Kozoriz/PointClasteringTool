#pragma once

#include "ServiceCommunicationDataMeneger.hpp"

class CloudeControler
{
public:
    CloudeControler( ServiceCommunicationDataMeneger& );

    void test( );

private:
    ServiceCommunicationDataMeneger& mDataMenegerService;
};
