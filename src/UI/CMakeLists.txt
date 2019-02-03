set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file( GLOB HEADERS
  impl/*.hpp
  *.hpp
)

file( GLOB SOURCES
  impl/*.cpp
  *.cpp
)

include_directories(
  ${COMPONENTS_DIR}
  ${COMPONENTS_DIR}/Common
  ${UTILS_DIR})

file ( GLOB FORMS
  impl/forms/*.ui
)
qt5_wrap_ui(FORM_H ${FORMS})

set(LIB_NAME UI)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS} ${FORM_H})

target_link_libraries(${LIB_NAME}
    PUBLIC
    ${PCL_LIBRARIES}
    ${Boost_LIBRARIES}
    -pthread )

qt5_use_modules(${LIB_NAME} Core Gui Widgets)


