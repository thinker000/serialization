cmake_minimum_required(VERSION 3.10)
project(Serializelib)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(include)

# 添加库
add_library(Serializelib STATIC
    src/my_library.cpp
    src/serializable.cpp
)

# 安装头文件
install(DIRECTORY include/ DESTINATION include)
# 安装库文件
install(TARGETS Serializelib DESTINATION lib)
