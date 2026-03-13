cmake_minimum_required(VERSION 3.13)
project(AP)

set(CMAKE_CXX_STANDARD 14)

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
# )
#For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(submodules/googletest-release-1.11.0) # <--- 对应你解压的实际文件夹名

include_directories(include/ 
    submodules/googletest-release-1.11.0/googletest/include 
    submodules/googletest-release-1.11.0/googlemock/include
)

add_executable(main
        src/main.cpp
        src/hw1.cpp
        src/unit_test.cpp
)
target_link_libraries(main
        gtest
        gtest_main
        gmock
)
