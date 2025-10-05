//
// Created by Ko-chieh Yin on 9/21/25.
//

#ifndef STUDY_ALGORITHMS_ARRAYLIST_H
#define STUDY_ALGORITHMS_ARRAYLIST_H

#include <algorithm>
#include <ostream>
#include <iterator>
#include <system_error>
#include <vector>
#include "linearList.h"

template<class T>
class arrayList final : public linearList<T> {
    friend std::ostream& operator<<(std::ostream& out, const arrayList<T>& x) {
        x.output(out);
        return out;
    }

private:
    // 内部类 iterator
    class iterator {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;

        explicit iterator(T* thePosition = nullptr) : position(thePosition) {}

        T& operator*() const { return *position; }
        T* operator->() const { return &*position; }

        iterator& operator++() { ++position; return *this; }
        iterator operator++(int) { iterator old = *this; ++position; return old; }

        iterator& operator--() { --position; return *this; }
        iterator operator--(int) { iterator old = *this; --position; return old; }

        bool operator!=(const iterator& rhs) const { return position != rhs.position; }
        bool operator==(const iterator& rhs) const { return position == rhs.position; }

        iterator operator+(size_t n) const { return iterator(position + n); }
        iterator operator-(size_t n) const { return iterator(position - n); }
        difference_type operator-(const iterator& other) const { return position - other.position; }

    private:
        T* position;
    };

public:
    explicit arrayList(size_t initialCapacity = 10, float loadFactor = 0.5);
    arrayList(const arrayList<T>&);
    arrayList<T>& operator=(const arrayList<T>&);
    ~arrayList() override { delete[] element; }

    [[nodiscard]] bool empty() const override { return listSize == 0; }
    [[nodiscard]] size_t size() const override { return listSize; }

    const T& get(size_t index) const override;
    std::optional<size_t> indexOf(const T& element) const override;
    void erase(size_t index) override;
    void insert(size_t index, const T& element) override;
    void output(std::ostream& out) const override;

    [[nodiscard]] int capacity() const { return arrayLength; }

    iterator begin() { return iterator(element); }
    iterator end() { return iterator(element + listSize); }
    iterator begin() const { return iterator(element); }
    iterator end() const { return iterator(element + listSize); }

private:
    void checkIndex(size_t index) const;

    T* element;
    //实际容量
    size_t listSize;
    //数组长度
    size_t arrayLength;
    float loadFactor;
};

// 构造函数
template<class T>
arrayList<T>::arrayList(size_t initialCapacity, float theLoadFactor) {
    if (initialCapacity < 1) throw std::system_error(std::make_error_code(std::errc::invalid_argument));
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
    loadFactor = theLoadFactor;
}

// 拷贝构造
template<class T>
arrayList<T>::arrayList(const arrayList<T>& list) {
    arrayLength = list.arrayLength;
    listSize = list.listSize;
    element = new T[arrayLength];
    loadFactor = list.loadFactor;
    std::copy(list.element, list.element + listSize, element);
}

// operator=
template<class T>
arrayList<T>& arrayList<T>::operator=(const arrayList<T>& rhs) {
    if (this != &rhs) {
        delete[] element;
        arrayLength = rhs.arrayLength;
        listSize = rhs.listSize;
        element = new T[arrayLength];
        std::copy(rhs.element, rhs.element + listSize, element);
        loadFactor = rhs.loadFactor;
    }
    return *this;
}

template<class T>
void arrayList<T>::checkIndex(size_t index) const {
    if (index >= listSize) throw std::system_error(std::make_error_code(std::errc::invalid_argument));
}

template<class T>
const T& arrayList<T>::get(size_t index) const {
    checkIndex(index);
    return element[index];
}

template<class T>
std::optional<size_t> arrayList<T>::indexOf(const T& e) const {
    for (size_t i = 0; i < listSize; i++) {
        if (e == element[i]) return i;
    }
    return {};
}

template<class T>
void arrayList<T>::erase(size_t index) {
    checkIndex(index);
    std::copy(element + index + 1, element + listSize, element + index);
    --listSize;
}

template<class T>
void arrayList<T>::insert(size_t index, const T& e) {
    if (index > listSize) throw std::out_of_range("插入位置非法");

    if (listSize >= arrayLength) {
        size_t newLength = std::max(static_cast<size_t>(arrayLength * (1 + loadFactor)), size_t(1));
        T* newElement = new T[newLength];
        std::copy(element, element + listSize, newElement);
        delete[] element;
        element = newElement;
        arrayLength = newLength;
    }

    std::copy_backward(element + index, element + listSize, element + listSize + 1);
    element[index] = e;
    ++listSize;
}

template<class T>
void arrayList<T>::output(std::ostream& out) const {
    std::copy(element, element + listSize, std::ostream_iterator<T>(out, " "));
    out << std::endl;
}

#endif //STUDY_ALGORITHMS_ARRAYLIST_H