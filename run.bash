#!/bin/bash

# 设置项目目录
PROJECT_DIR=$(pwd)

# 设置构建目录
BUILD_DIR=${PROJECT_DIR}/build

# 可执行文件的名称
EXECUTABLE_NAME=MyProject

# 创建构建目录
mkdir -p $BUILD_DIR

# 进入构建目录
cd $BUILD_DIR

# 运行 CMake 以生成构建系统文件
cmake ..

# 编译项目
cmake --build .

# 检查是否需要运行可执行文件
if [ -f "${PROJECT_DIR}/bin/${EXECUTABLE_NAME}" ]; then
    echo "Running ${EXECUTABLE_NAME}..."
    "${PROJECT_DIR}/bin/${EXECUTABLE_NAME}"
else
    echo "Executable ${EXECUTABLE_NAME} not found."
fi