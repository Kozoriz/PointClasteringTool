#pragma once

namespace common
{
class AppointeeImpl
{
public:
    template < class Type >
    static void
    appointee( Type& t, decltype( t.mImpl ) const & newImpl )
    {
        t.mImpl = newImpl;
    }
};
}
