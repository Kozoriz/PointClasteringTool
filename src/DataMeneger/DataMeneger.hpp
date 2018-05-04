#pragma once

#include <memory>
#include <vector>

#include <boost/thread.hpp>

#include "../Common/app_type/Point.hpp"

class DataMenegerImpl;

namespace common
{
struct Point;
}

class DataMeneger
{
public:
    DataMeneger( );

    void start( );

    bool creatr_cloude( bool );
    bool get_cloude( std::vector< common::Point >& cloude );

public:
    std::shared_ptr< DataMenegerImpl > mImpl;
};
