#pragma once

#include <functional>
#include <vector>

#include <boost/log/trivial.hpp>
#include <boost/signals2.hpp>
#include "boost/bind.hpp"

#include "../DataMeneger/DataMeneger.hpp"
#include "../Common/app_type/Point.hpp"

namespace common
{

template < typename SendType, typename AnswerType, typename UsedType >
class Communications
{
public:
    using signal_type = boost::signals2::signal< AnswerType( SendType ) >;
    using slot_type = typename signal_type::slot_type;

    Communications( UsedType const& mUsedType )
        : mType( mUsedType )
    {
    }

    void
    connect( slot_type const& _slot )
    {
        mSignal.connect( _slot );
    }

    AnswerType
    talk( SendType const& sendType )
    {
        auto retur_value = mSignal( sendType );
        return static_cast< AnswerType >( *retur_value );
    }

private:
    signal_type mSignal;
    UsedType mType;
};

template<typename SendType , typename UsedType>
class Communications< SendType, void , UsedType >
{
public:
    using signal_type = boost::signals2::signal< void( SendType ) >;
    using slot_type = typename signal_type::slot_type;

    Communications( UsedType const& mUsedType )
        : mType( mUsedType )
    {
    }

    void
    connect( slot_type const& _slot )
    {
        mSignal.connect( _slot );
    }

    void
    talk( SendType const& sendType )
    {
        mSignal( sendType );
    }

private:
    signal_type mSignal;
    UsedType mType;
};

template<typename AnswerType , typename UsedType>
class Communications< void , AnswerType , UsedType >
{
public:
    using signal_type = boost::signals2::signal< AnswerType( void ) >;
    using slot_type = typename signal_type::slot_type;

    Communications( UsedType const& mUsedType )
        : mType( mUsedType )
    {
    }

    void
    connect( slot_type const& _slot )
    {
        mSignal.connect( _slot );
    }

    AnswerType
    talk( )
    {
        auto retur_value = mSignal( );
        return static_cast< AnswerType >( *retur_value );
    }

private:
    signal_type mSignal;
    UsedType mType;
};


//Move in new file
class CommunicationsWithDataMeneger
{
public:
  CommunicationsWithDataMeneger( DataMeneger& dm)
    : dataMeneger(dm)
    , create_cloude_signal(dm)
    , get_cloude_signal(dm)
  {

  }

  void conections_all()
  {
    create_cloude_signal.connect( boost::bind( &DataMeneger::creatr_cloude, &dataMeneger ) );
    get_cloude_signal.connect( boost::bind( &DataMeneger::get_cloude, &dataMeneger, _1 ) );
  }

private:
   DataMeneger& dataMeneger;

public:
   common::Communications< void , bool , DataMeneger > create_cloude_signal;
   common::Communications< std::vector< common::Point >&, void, DataMeneger > get_cloude_signal;

};


}
