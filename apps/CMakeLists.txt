project(ArgExample)

add_executable(ArgExample application.cpp)
target_link_libraries(ArgExample PRIVATE ArgLib)
