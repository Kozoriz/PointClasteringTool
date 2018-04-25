cmake_minimum_required (VERSION 3.5.1)
project (DIPLOM_v2.1)

set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_BINARY_DIR       ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_CXX_STANDARD 14)

find_package(Qt5 COMPONENTS Core Gui Qml Quick REQUIRED)

find_package(Boost 1.58.0 COMPONENTS log_setup log program_options thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_definitions(-DBOOST_LOG_DYN_LINK=1)

add_subdirectory(App)
add_subdirectory(CloudeControler)
add_subdirectory(DataMeneger)
add_subdirectory(UI)
add_subdirectory(Common)


