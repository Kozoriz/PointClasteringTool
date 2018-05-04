#include "LifeCycle.hpp"

#include "../DataMeneger/impl/DataMenegerImpl.hpp"
#include "../UI/impl/RenderImpl.hpp"

#include <boost/log/trivial.hpp>
#include <functional>

LifeCycle::LifeCycle( )
    : dataMeneger( )
    , render( )
    , create_cloude_signal( dataMeneger )
{
}

void
LifeCycle::init( )
{
    BOOST_LOG_TRIVIAL( trace ) << "Init project";
    common::AppointeeImpl::appointee< DataMeneger >( dataMeneger,
                                                     std::make_shared< DataMenegerImpl >( ) );
    common::AppointeeImpl::appointee< Render >( render, std::make_shared< RenderImpl >( ) );

    create_cloude_signal.connect( boost::bind( &DataMeneger::creatr_cloude, &dataMeneger, _1 ) );
}

void
LifeCycle::start( )
{
    BOOST_LOG_TRIVIAL( trace ) << "Start project";
    render.start_app( );
    create_cloude_signal.talk( true );
    BOOST_LOG_TRIVIAL( trace ) << "Super" << create_cloude_signal.talk( true );
}

void
LifeCycle::stop( )
{
    BOOST_LOG_TRIVIAL( trace ) << "Stop project";
}
