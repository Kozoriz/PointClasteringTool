#include "LifeCycle.hpp"

#include "../DataMeneger/impl/DataMenegerImpl.hpp"
#include "../UI/impl/RenderImpl.hpp"

#include <boost/log/trivial.hpp>
#include <functional>

LifeCycle::LifeCycle( )
    : mRender( )
    , mDataMeneger( )
    , mControlerWithDataMeneger( mDataMeneger )

    , mControler( mControlerWithDataMeneger )

{
}

void
LifeCycle::init( )
{
    BOOST_LOG_TRIVIAL( trace ) << "Init project";
    common::AppointeeImpl::appointee< DataMeneger >( mDataMeneger,
                                                     std::make_shared< DataMenegerImpl >( ) );
    common::AppointeeImpl::appointee< Render >( mRender, std::make_shared< RenderImpl >( ) );
}

void
LifeCycle::start( )
{
    BOOST_LOG_TRIVIAL( trace ) << "Start project";
    mControler.test( );
    mRender.start_app( );
}

void
LifeCycle::stop( )
{
    BOOST_LOG_TRIVIAL( trace ) << "Stop project";
}
