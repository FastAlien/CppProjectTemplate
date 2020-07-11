project(ProjectLib)

add_library(ProjectLib STATIC
		project/factorial.cpp)

target_include_directories(ProjectLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
