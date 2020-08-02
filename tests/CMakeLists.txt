project(ArgTest)

add_executable(ArgTest
        main.test.cpp
        arg/ArgumentParser.test.cpp
        arg/HelpFormatter.test.cpp)

target_link_libraries(ArgTest PRIVATE
        ArgLib
        Catch2)

catch_discover_tests(ArgTest)
