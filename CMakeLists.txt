cmake_minimum_required(VERSION 3.16)
project(StudyDataStruct VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#include_directories(
#        ${CMAKE_CURRENT_SOURCE_DIR}/include
#)

# 添加子目录模块
add_subdirectory(线性表)
add_subdirectory(树)


add_subdirectory(test/googletest)
add_subdirectory(test)
enable_testing()

