# 设置CMake的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(MyProject VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 查找所有源文件
file(GLOB SOURCES "Model/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 添加可执行文件
add_executable(MyProject ${SOURCES})

# 设置目标属性
target_include_directories(MyProject PRIVATE ${PROJECT_SOURCE_DIR}/include)

# 添加调试信息
target_compile_options(MyProject PRIVATE -g)

# 添加编译选项（可选）
# target_compile_options(MyProject PRIVATE -Wall -Wextra -pedantic)