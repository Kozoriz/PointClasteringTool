cmake_minimum_required (VERSION ${CMAKE_VERSION})
set(NAME_LIB data_manager)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
#link_directories(${PCL_INCLUDE_DIRS})
#add_definitions(${PCL_DEFINITIONS})

file( GLOB HEADERS
         *.hpp
         impl/*.hpp
)

file( GLOB SOURCES
         *.cpp
         impl/*.cpp
)

add_library(${NAME_LIB} ${SOURCES} ${HEADERS})

target_link_libraries(${NAME_LIB} PUBLIC
#    ${Boost_SYSTEM_LIBRARY}
#    ${Boost_LOG_LIBRARY}
    ${PCL_LIBRARIES}
    common
    -pthread )
