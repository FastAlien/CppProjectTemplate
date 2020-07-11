project(ProjectTest)

add_executable(ProjectTest
		test.cpp)

target_link_libraries(ProjectTest PRIVATE
		ProjectLib
		Catch2)

add_test(ProjectTest main.cpp)
