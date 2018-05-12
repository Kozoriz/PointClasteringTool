cmake_minimum_required (VERSION ${CMAKE_VERSION})
project(controler)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file( GLOB HEADERS
         Controler.hpp
)

file( GLOB SOURCES
         Controler.cpp
)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_LOG_LIBRARY}
    render
    data_meneger
    common
    -pthread )
