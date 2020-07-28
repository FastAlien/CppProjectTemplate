project(ArgTest)

add_executable(ArgTest
		test.cpp
		arg/arguments_test.cpp)

target_link_libraries(ArgTest PRIVATE
		ArgLib
		Catch2)

catch_discover_tests(ArgTest)
