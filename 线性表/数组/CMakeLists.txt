# 线性表数组实现
set(CMAKE_CXX_STANDARD 17)



include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../utils
)


add_executable(linearList linearList.cpp )