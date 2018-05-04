#include <Controler.hpp>

#include <boost/log/trivial.hpp>

CloudeControler::CloudeControler( ServiceCommunicationDataMeneger& dataMenegerService )
    : mDataMenegerService( dataMenegerService )
{
    BOOST_LOG_TRIVIAL( trace ) << "Create CloudeControler";
}

void
CloudeControler::test( )
{
    mDataMenegerService.create_cloude_signal.talk( true );
    BOOST_LOG_TRIVIAL( debug ) << mDataMenegerService.create_cloude_signal.talk( true );
}
