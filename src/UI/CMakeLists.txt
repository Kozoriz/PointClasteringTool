set(CMAKE_AUTOMOC ON)

file( GLOB HEADERS
         Render.hpp
         impl/RenderImpl.hpp
         impl/QtRenderObject.hpp
)

file( GLOB SOURCES
         Render.cpp
         impl/RenderImpl.cpp
         impl/QtRenderObject.cpp
)

set ( RESOURCES
 impl/Resources/qml.qrc
)

include_directories(
  ${COMPONENTS_DIR}
  ${COMPONENTS_DIR}/Common)

set(LIB_NAME UI)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

target_link_libraries(${LIB_NAME}
    PUBLIC
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_LOG_LIBRARY}
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    -pthread )

