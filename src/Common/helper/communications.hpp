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

template < typename SendType, typename AnswerType >
class Communications
{
  using signal_type = boost::signals2::signal< AnswerType( SendType ) >;
  using slot_type = typename signal_type::slot_type;

public:

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
};

template<typename SendType >
class Communications< SendType, void >
{
  using signal_type = boost::signals2::signal< void( SendType ) >;
  using slot_type = typename signal_type::slot_type;

public:

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
};

template<typename AnswerType >
class Communications< void , AnswerType  >
{
  using signal_type = boost::signals2::signal< AnswerType( void ) >;
  using slot_type = typename signal_type::slot_type;
public:
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
};


//Move in new file
class CommunicationsWithDataMeneger
{
public:
  CommunicationsWithDataMeneger( DataMeneger& dm)
    : dataMeneger(dm)
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
   common::Communications< void , bool  > create_cloude_signal;
   common::Communications< std::vector< common::Point >&, void > get_cloude_signal;

};


}
