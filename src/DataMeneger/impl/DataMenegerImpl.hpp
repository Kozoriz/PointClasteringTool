#pragma once

#include <vector>

#include "../Common/app_type/Point.hpp"

class DataMenegerImpl
{
public:
    DataMenegerImpl( ) = default;
    bool create_random_points_clude( );
    const common::Points &getCloude( ) const;

private:
    common::Points mCloude;
};
