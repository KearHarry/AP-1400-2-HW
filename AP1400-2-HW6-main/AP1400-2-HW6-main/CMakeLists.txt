cmake_minimum_required(VERSION 3.14)
project(AP)

set(CMAKE_CXX_STANDARD 20)

# 使用 FetchContent 从源码编译 GTest，彻底解决 Anaconda 环境或者系统自带的 GTest 产生的编译器 ABI 不匹配和 undefined reference 问题
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# 强制 GTest 匹配当前环境的运行库
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/unit_test.cpp
)

# 链接通过源码现场编译生成的 targets
target_link_libraries(main
        gtest
        gtest_main
        gmock
        gmock_main
)

# 确保在Windows的MinGW下编译大文件不出错
if(WIN32 AND MINGW)
    add_compile_options(-Wa,-mbig-obj)
    target_link_libraries(main pthread)
endif()

configure_file(${CMAKE_SOURCE_DIR}/resources/flights.txt ${CMAKE_CURRENT_BINARY_DIR}/flights.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/resources/lung_cancer.csv ${CMAKE_CURRENT_BINARY_DIR}/lung_cancer.csv COPYONLY)