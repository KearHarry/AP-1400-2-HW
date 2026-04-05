cmake_minimum_required(VERSION 3.14)
project(AP)

set(CMAKE_CXX_STANDARD 20)

# 使用 FetchContent 源码编译 GTest 防止 MinGW 和 MSVC 预编译库产生 ABI 冲突 (引发 undefined reference)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/unit_test.cpp
        src/espresso_based.cpp
        src/cappuccino.cpp
        src/mocha.cpp
)

# 链接通过源码编译的 gtest 和 gtest_main
target_link_libraries(main
        gtest
        gmock
        gtest_main
        gmock_main
)