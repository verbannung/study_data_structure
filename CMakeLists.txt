cmake_minimum_required(VERSION 3.16)
project(StudyAlgorithms)

set(CMAKE_CXX_STANDARD 17)

# 添加子目录
add_subdirectory(线性表/数组)
add_subdirectory(线性表/链表)

# 未来可以添加更多子包
# add_subdirectory(栈和队列)
# add_subdirectory(树)
# add_subdirectory(图)
# add_subdirectory(排序)
# add_subdirectory(搜索)