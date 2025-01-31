cmake_minimum_required(VERSION 3.10)
project(MyProgram)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加源文件
set(SOURCES Model.cpp)

# 生成可执行文件
add_executable(my_program ${SOURCES})
