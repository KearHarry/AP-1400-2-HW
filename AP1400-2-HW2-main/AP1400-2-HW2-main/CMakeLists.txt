cmake_minimum_required(VERSION 3.13)
project(AP)

set(CMAKE_CXX_STANDARD 20)

# 自动指向当前工作空间的 OpenSSL 路径
set(OPENSSL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../OpenSSL-Win64" CACHE PATH "OpenSSL root directory" FORCE)

# 完全跳过 find_package(OpenSSL)，手动定义所需变量和目标
set(OPENSSL_FOUND TRUE)
set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_CRYPTO_LIBRARY "${OPENSSL_ROOT_DIR}/lib/VC/x64/MT/libcrypto.lib")
set(OPENSSL_SSL_LIBRARY "${OPENSSL_ROOT_DIR}/lib/VC/x64/MT/libssl.lib")
set(OPENSSL_LIBRARIES "${OPENSSL_SSL_LIBRARY}" "${OPENSSL_CRYPTO_LIBRARY}")
set(OPENSSL_VERSION "3.6.1")

if(NOT TARGET OpenSSL::Crypto)
    add_library(OpenSSL::Crypto UNKNOWN IMPORTED)
    set_target_properties(OpenSSL::Crypto PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_INCLUDE_DIR}"
        IMPORTED_LOCATION "${OPENSSL_CRYPTO_LIBRARY}"
    )
endif()
if(NOT TARGET OpenSSL::SSL)
    add_library(OpenSSL::SSL UNKNOWN IMPORTED)
    set_target_properties(OpenSSL::SSL PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${OPENSSL_INCLUDE_DIR}"
        IMPORTED_LOCATION "${OPENSSL_SSL_LIBRARY}"
        INTERFACE_LINK_LIBRARIES OpenSSL::Crypto
    )
endif()

# 注释掉报错的 find_package
# find_package(OpenSSL REQUIRED)

# 指向您下载并解压的 GoogleTest 目录
add_subdirectory(external/googletest-main)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/server.cpp
        src/client.cpp
        src/crypto.cpp
        src/unit_test.cpp
)
target_link_libraries(main
        OpenSSL::SSL
        gtest
        gtest_main
        gmock
        gmock_main
)