#pragma once

#include <vector>

namespace common
{
struct Point;
}

class DataMenegerImpl
{
public:
    DataMenegerImpl( ) = default;
    bool create_random_points_clude( );
    const std::vector< common::Point >& getCloude( ) const;

private:
    std::vector< common::Point > mCloude;
};
