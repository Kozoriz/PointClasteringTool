set(CMAKE_AUTOMOC ON)

file( GLOB HEADERS
  impl/.*hpp
  *.hpp
)

file( GLOB SOURCES
  impl/*.cpp
  *.cpp
)

set ( RESOURCES
 impl/Resources/qml.qrc
)

include_directories(
  ${COMPONENTS_DIR}
  ${COMPONENTS_DIR}/Common
  ${UTILS_DIR})

set(LIB_NAME UI)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

target_link_libraries(${LIB_NAME}
    PUBLIC
    ${Boost_LIBRARIES}
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    -pthread )

