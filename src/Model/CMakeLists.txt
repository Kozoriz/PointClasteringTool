
include_directories(
  ${COMPONENTS_DIR}
  ${UTILS_DIR})

file(GLOB SOURCES */*.cpp)
file(GLOB HEADERS */*.h)


set(LIB_NAME Model)

add_library(${LIB_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${LIB_NAME} Utils)
