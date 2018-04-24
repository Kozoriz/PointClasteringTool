#pragma once

namespace common
{
class AppointeeImpl
{
public:
    template < class Type >
    static void
    appointee( Type& t, const decltype( t.mImpl ) & newImpl )
    {
        t.mImpl = newImpl;
    }
};
}
