project(ArgLib)

add_library(ArgLib STATIC
		arg/option.cpp
		arg/parse.cpp
		arg/format.cpp)

target_include_directories(ArgLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
