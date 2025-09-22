# 线性表数组实现
set(CMAKE_CXX_STANDARD 17)

# 创建库
#add_library(linearList
#    linearList.cpp
#        ../utils.cpp
#)


# 设置头文件包含目录
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../utils
)

# 创建可执行文件
add_executable(linearList linearList.cpp )