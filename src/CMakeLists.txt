cmake_minimum_required(VERSION 3.20)

file(
    GLOB_RECURSE
    SOURCE_FILES
    CONFIGURE_DEPENDS
    "*.cpp"
)

list(REMOVE_ITEM SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

add_library(
    DUMBLANG_CORE
    STATIC
    ${SOURCE_FILES}
)

include(FetchContent)
FetchContent_Declare(
    MagicEnum
    GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
    GIT_TAG v0.9.8
)

FetchContent_MakeAvailable(MagicEnum)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

target_include_directories(
    DUMBLANG_CORE
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    DUMBLANG_CORE
    PUBLIC
    magic_enum::magic_enum
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    DUMBLANG_CORE
)

target_compile_options(
    DUMBLANG_CORE
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -Wshadow
    -Wconversion

    -fno-omit-frame-pointer
    -O1
    -g
)
