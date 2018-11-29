include_directories(
  ${COMPONENTS_DIR}
  ${UTILS_DIR})

file( GLOB HEADERS
	 LifeCycle.hpp
)

file( GLOB SOURCES
	 LifeCycle.cpp
)

add_executable( ${PROJECT_NAME} main.cpp ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${PCL_LIBRARIES}
    ${Boost_LIBRARIES}
    UI
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
    -pthread
    Utils
    Model
    Controller)

