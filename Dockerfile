FROM  ubuntu:22.04

# 替换apt源为国内阿里云源，避免 apt-get 更新慢或被墙
RUN sed -i 's/archive.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list && \
    sed -i 's/security.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list

# 安装基础编译环境：GCC/G++ 11，CMake，GDB 和 Git
RUN apt-get -qq update \
    && DEBIAN_FRONTEND=noninteractive apt-get -qq install -y gcc-11 g++-11 cmake gdb git \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 100 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*


# 全局安装 Google Test，这样7个作业都能复用
WORKDIR /usr/src/gtest_build
RUN git clone --depth=1 -b main https://gitee.com/mirrors/googletest.git \
    && cd googletest \
    && mkdir build && cd build \
    && cmake .. && make && make install

WORKDIR /workspace
CMD ["/bin/bash"]
