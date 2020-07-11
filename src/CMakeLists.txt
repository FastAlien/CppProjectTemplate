project(ProjectLib)

add_library(ProjectLib STATIC
		project/Sample.cpp)

target_include_directories(ProjectLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
