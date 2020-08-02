project(ProjectTest)

add_executable(ProjectTest
		main.test.cpp
		project/factorial.test.cpp)

target_link_libraries(ProjectTest PRIVATE
		ProjectLib
		Catch2)

catch_discover_tests(ProjectTest)
