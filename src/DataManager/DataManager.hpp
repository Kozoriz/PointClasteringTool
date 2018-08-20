#pragma once

#include <memory>
#include <vector>

class DataManagerImpl;
namespace common {
class AppointeeImpl;
struct Point;
}

namespace common
{
struct Point;
}

class DataManager
{
public:
    DataManager( );

    bool creatr_cloude( );
    void get_cloude( std::vector< common::Point >& cloude );

private:
    friend class common::AppointeeImpl;
    std::shared_ptr< DataManagerImpl > mImpl;
};
