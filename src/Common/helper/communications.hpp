#pragma once

#include <functional>

#include <boost/log/trivial.hpp>
#include <boost/signals2.hpp>
#include "boost/bind.hpp"

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
}
