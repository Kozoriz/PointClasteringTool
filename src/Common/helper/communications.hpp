#pragma once

#include <functional>
#include <vector>

#include <boost/log/trivial.hpp>
#include <boost/signals2.hpp>
#include "boost/bind.hpp"

#include "../../DataManager/DataManager.hpp"
#include "../../Common/app_type/Point.hpp"

#include "Model/Common/pointcloud.h"

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
class CommunicationsWithDataManager
{
public:
  CommunicationsWithDataManager( DataManager& dm)
    : dataMeneger(dm)
  {

  }

  void conections_all()
  {
    create_cloude_signal.connect( boost::bind( &DataManager::creatr_cloude, &dataMeneger ) );
    get_cloude_signal.connect( boost::bind( &DataManager::get_cloude, &dataMeneger, _1 ) );
  }

private:
   DataManager& dataMeneger;

public:
   common::Communications< void , bool  > create_cloude_signal;
   common::Communications< const PointCloud**, void > get_cloude_signal;

};


}
