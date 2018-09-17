include_directories(${UTILS_INCLUDE_DIR})

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
    UI
    DataManager
    CommonLib
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    -pthread
    Utils
    Model)

