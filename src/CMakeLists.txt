project(ArgLib)

add_library(ArgLib STATIC
        arg/ArgumentParser.cpp
        arg/HelpFormatter.cpp)

target_include_directories(ArgLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
