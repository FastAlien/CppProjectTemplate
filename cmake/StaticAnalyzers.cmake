option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
option(ENABLE_INCLUDE_WHAT_YOU_USE "Enable static analysis with include-what-you-use" OFF)

if (ENABLE_CPPCHECK)
    find_program(CPPCHECK cppcheck)
    if (CPPCHECK)
        set(CMAKE_CXX_CPPCHECK ${CPPCHECK}
                --quiet
                --enable=all
                --std=c++17
                --verbose
                --inline-suppr
                --suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/.cppcheck-suppress)
    else ()
        message(SEND_ERROR "cppcheck executable not found")
    endif ()
endif ()

if (ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY clang-tidy)
    if (CLANG_TIDY)
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY} -extra-arg=-Wno-unknown-warning-option)
    else ()
        message(SEND_ERROR "Executable for clang-tidy not found")
    endif ()
endif ()

if (ENABLE_INCLUDE_WHAT_YOU_USE)
    find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
    if (INCLUDE_WHAT_YOU_USE)
        set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE}
                -Xiwyu --quoted_includes_first
                -Xiwyu --cxx17ns)
    else ()
        message(SEND_ERROR "Executable for include-what-you-use not found")
    endif ()
endif ()
