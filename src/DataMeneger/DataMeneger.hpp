#pragma once

#include <memory>
#include <vector>

class DataMenegerImpl;
namespace common {
class AppointeeImpl;
struct Point;
}

namespace common
{
struct Point;
}

class DataMeneger
{
public:
    DataMeneger( );

    bool creatr_cloude( bool );
    bool get_cloude( std::vector< common::Point >& cloude );

private:
    friend class common::AppointeeImpl;
    std::shared_ptr< DataMenegerImpl > mImpl;
};
