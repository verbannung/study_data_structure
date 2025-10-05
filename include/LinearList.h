//
// Created by Ko-chieh Yin on 9/24/25.
// 统一的线性表接口定义
//

#ifndef STUDYALGORITHMS_LINEARLIST_H
#define STUDYALGORITHMS_LINEARLIST_H

#include <cstddef>
#include <optional>
#include <iosfwd>
#include <algorithm>

template<class T>
class LinearList {
public:
    virtual ~LinearList() = default;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual const T& get(size_t index) const = 0;
    virtual std::optional<size_t> indexOf(const T& element) const = 0;
    virtual void erase(size_t index) = 0;
    virtual void insert(size_t index, const T& element) = 0;
    virtual void output(std::ostream& out) const = 0;
};

// 二倍扩容工具函数
// 如果说是每一次都需要扩展的话，那么就需要O(n^2)的时间复杂度,空间复杂度是O(n)
// 如果说是每一次扩展两倍，那么仅仅需要O(n)的时间复杂度,是空间复杂度是O(n)
template<class T>
void changeLength1D(T*& a, size_t oldLength, size_t newLength) {
    T* temp = new T[newLength];
    size_t number = std::min(oldLength, newLength);
    // 调用拷贝赋值
    std::copy(a, a + number, temp);
    delete[] a;
    a = temp;
}

#endif //STUDYALGORITHMS_LINEARLIST_H