cmake_minimum_required(VERSION 2.8)

project (DIPLOM_v2.1)
set (PROJECT DIPLOM_v2.1)

### FLAGS/PACKAGES
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -w -O0")
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BINARY_DIR       ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/lib)

option(ENABLE_LOG "If logging needed" ON)

### LOGGER
if (ENABLE_LOG)
  if (EXISTS "$ENV{LOG4CPLUS_DIRECTORY}/lib/liblog4cplus.a")
    set(LOGGER_HOME $ENV{LOG4CPLUS_DIRECTORY})
    if (EDISON_BUILD)
      set(LOGGER_HOME "$ENV{LOG4CPLUS_DIRECTORY}i586/")
    endif()
    add_definitions(-DENABLE_LOG)
    set(LOG4CPLUS_INCLUDE_DIR "${LOGGER_HOME}include")
    set(LOG4CPLUS_LIB_DIR "${LOGGER_HOME}lib")
    include_directories ( ${LOG4CPLUS_INCLUDE_DIR} )
  else()
    message(FATAL_ERROR " LOG4CPLUS is not present. Please install log4cplus logger ver. >= 2.0.0!")
  endif()
endif(ENABLE_LOG)


### qt
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Gui Qml Quick Widgets REQUIRED)

### pcl
find_package(PCL 1.2 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_definitions(-DPCL_INCLUDED=1)

### boost
set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.62 COMPONENTS program_options system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_definitions(-DBOOST_LOG_DYN_LINK=1)

### variables
set(COMPONENTS_DIR ${CMAKE_SOURCE_DIR})
set(UTILS_DIR ${COMPONENTS_DIR}/3rd-party/c-plus-utils/src/utils/include)

### install
set(INSTALL_DIR ${EXECUTABLE_OUTPUT_PATH})
set(INSTAL_FILES
../config/log4cplus.properties
../config/config.ini
)
file(COPY ${INSTAL_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
install(FILES ${INSTAL_FILES} DESTINATION ${INSTALL_DIR})

### sub dirs
add_subdirectory(3rd-party)
add_subdirectory(App)
add_subdirectory(UI)
add_subdirectory(Model)
add_subdirectory(Controller)

