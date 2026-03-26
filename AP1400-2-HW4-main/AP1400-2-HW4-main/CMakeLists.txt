cmake_minimum_required(VERSION 3.14)
project(AP)

set(CMAKE_CXX_STANDARD 20)

# 自动下载并包含 Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
# 对于 Windows，通常需要加上这段以防 gtest 和你在 CRT 产生冲突
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/unit_test.cpp
)

# 确保链接到 gtest 和 gmock
target_link_libraries(main
        gtest_main
        gmock
)