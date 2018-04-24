cmake_minimum_required (VERSION ${CMAKE_VERSION})
project(render)

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

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_LOG_LIBRARY}
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    -pthread )
