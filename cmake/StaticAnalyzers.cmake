# cppcheck
find_program(CPPCHECK cppcheck)
if (CPPCHECK)
    set(CMAKE_CXX_CPPCHECK ${CPPCHECK}
            --quiet
            --enable=all
            --std=c++17
            --verbose
            --suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/cppcheck.suppress)
else ()
    message("cppcheck was not found")
endif ()

# clang-tidy
find_program(CLANGTIDY clang-tidy)
if (CLANGTIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -extra-arg=-Wno-unknown-warning-option)
else ()
    message("clang-tidy was not found")
endif ()

# include-what-you-use
find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
if (INCLUDE_WHAT_YOU_USE)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE}
            --quoted-includes-first)
else ()
    message("include-what-you-use was not found")
endif ()
