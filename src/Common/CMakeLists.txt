find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})

file( GLOB HEADERS
    */*.hpp
)

file( GLOB SOURCES
    */*.cpp
)

set(LIB_NAME CommonLib)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${LIB_NAME}
    PUBLIC
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_LOG_LIBRARY}
    ${PCL_LIBRARIES}
        Qt5::Core
    -pthread )
