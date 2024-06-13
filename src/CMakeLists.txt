file(GLOB_RECURSE SRC_LIST "*.cpp")
add_library(compilery STATIC ${SRC_LIST})
target_include_directories(compilery PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
