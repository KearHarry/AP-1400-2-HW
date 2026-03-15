cmake_minimum_required(VERSION 3.14)
project(AP)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../googletest-1.14.0"
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/bst.cpp
        src/unit_test.cpp
)
target_link_libraries(main
        gtest
        gmock
)