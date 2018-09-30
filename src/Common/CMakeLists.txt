file( GLOB HEADERS
    */*.hpp
)

file( GLOB SOURCES
    */*.cpp
)

include_directories(
  ${COMPONENTS_DIR}
  ${UTILS_DIR})

set(LIB_NAME CommonLib)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${LIB_NAME}
    PUBLIC
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_LOG_LIBRARY}
    Qt5::Core
    -pthread )
