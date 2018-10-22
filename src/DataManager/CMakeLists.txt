file( GLOB HEADERS
         *.hpp
         impl/*.hpp
)

file( GLOB SOURCES
         *.cpp
         impl/*.cpp
)

include_directories(
  ${COMPONENTS_DIR}
  ${COMPONENTS_DIR}/Common
  ${UTILS_DIR})

set(LIB_NAME DataManager)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${LIB_NAME} PUBLIC
    CommonLib
    -pthread )
