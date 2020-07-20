project(ProjectTest)

add_executable(ProjectTest
		test.cpp
		project/arguments.cpp
		project/factorial.cpp)

target_link_libraries(ProjectTest PRIVATE
		ProjectLib
		Catch2)

catch_discover_tests(ProjectTest)
