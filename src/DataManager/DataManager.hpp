#pragma once

#include <memory>
#include <vector>
#include "Model/Common/pointcloud.h"

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
    void get_cloude(const PointCloud **cloud );

private:
    friend class common::AppointeeImpl;
    std::shared_ptr< DataManagerImpl > mImpl;
};
