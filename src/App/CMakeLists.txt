cmake_minimum_required (VERSION 3.5.1)

file( GLOB HEADERS
	 LifeCycle.hpp
)

file( GLOB SOURCES
	 LifeCycle.cpp
)

add_executable( ${PROJECT_NAME} main.cpp ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_LOG_LIBRARY}
    render
    data_manager
    common
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    -pthread )
