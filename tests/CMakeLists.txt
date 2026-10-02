cmake_minimum_required(VERSION 3.20)

set(
    TEST_SOURCES
    lexer/LexerTests.cpp
)

include(FetchContent)
FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.18.0
)

FetchContent_MakeAvailable(GoogleTest)

add_executable(
    DUMBLANG_TESTS
    ${TEST_SOURCES}
)

target_link_libraries(
    DUMBLANG_TESTS
    PRIVATE
    DUMBLANG_CORE
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(DUMBLANG_TESTS)

