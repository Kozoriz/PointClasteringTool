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
    using slot_type = typename boost::signals2::signal< AnswerType( SendType ) >::slot_type;
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
    boost::signals2::signal< AnswerType( SendType ) > mSignal;
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
    create_cloude_signal.connect( boost::bind( &DataMeneger::creatr_cloude, &dataMeneger, _1 ) );
    get_cloude_signal.connect( boost::bind( &DataMeneger::get_cloude, &dataMeneger, _1 ) );
  }

private:
   DataMeneger& dataMeneger;

public:
   common::Communications< bool, bool, DataMeneger > create_cloude_signal;
   common::Communications< std::vector< common::Point >&, bool, DataMeneger > get_cloude_signal;

};


}
