file(GLOB_RECURSE SRC_LIST "*.cpp")
add_executable(unit_test ${SRC_LIST})
target_link_libraries(unit_test compilery)