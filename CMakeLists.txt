cmake_minimum_required(VERSION 3.16)
project(CppProjectTemplate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/extern/catch2/cmake")

include(CTest)
include(Catch)

enable_testing()

add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(extern/catch2)
add_subdirectory(tests)
