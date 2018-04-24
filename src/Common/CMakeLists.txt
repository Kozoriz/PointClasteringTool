cmake_minimum_required (VERSION 3.5.1)
project(common)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file( GLOB HEADERS
    helper/app_helper.hpp
    app_type/Point.hpp
)

file( GLOB SOURCES
    app_type/Point.cpp
    converters/converters_pcl.cpp
)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_LOG_LIBRARY}
    -pthread )
