cmake_minimum_required(VERSION 2.8)

project (DIPLOM_v2.1)
set (PROJECT DIPLOM_v2.1)

### FLAGS/PACKAGES
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -w")
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BINARY_DIR       ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/lib)

find_package(Qt5 COMPONENTS Core Gui Qml Quick REQUIRED)

find_package(Boost 1.58.0 COMPONENTS program_options log system REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
add_definitions(-DBOOST_LOG_DYN_LINK=1)

set(COMPONENTS_DIR ${CMAKE_SOURCE_DIR})
set(UTILS_DIR ${COMPONENTS_DIR}/3rd-party/c-plus-utils/src/utils/include)

add_subdirectory(3rd-party)
add_subdirectory(App)
add_subdirectory(CloudController)
add_subdirectory(DataManager)
add_subdirectory(UI)
add_subdirectory(Common)
add_subdirectory(Model)

