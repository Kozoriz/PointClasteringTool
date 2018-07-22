cmake_minimum_required (VERSION 3.5.1)
project(common)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})

file( GLOB HEADERS
    helper/app_helper.hpp
    helper/communications.hpp
    converters/converters_pcl.hpp
    app_type/Point.hpp
)

file( GLOB SOURCES
    app_type/Point.cpp
)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_LOG_LIBRARY}
    ${PCL_LIBRARIES}
        Qt5::Core
    -pthread )
