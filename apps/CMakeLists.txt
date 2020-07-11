project(ProjectApp)

add_executable(ProjectApp application.cpp)
target_link_libraries(ProjectApp PRIVATE ProjectLib)
