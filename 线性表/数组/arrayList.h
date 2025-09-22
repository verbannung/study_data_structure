//
// Created by Ko-chieh Yin on 9/21/25.
//


#ifndef STUDY_ALGORITHMS_ARRAYLIST_H
#define STUDY_ALGORITHMS_ARRAYLIST_H
#include <algorithm>
#include <iosfwd>
#include <ostream>
#include <system_error>
#include <__system_error/errc.h>

#include "linearList.h"





template<class T>
class arrayList :public linearList<T> {

    friend std::ostream& operator<<(std::ostream& out,const arrayList<T>& x);



    //内部类 iterator
private:
    class iterator {
    public:
        //标记类型，标识迭代器的双向迭代能力
        typedef std::bidirectional_iterator_tag iterator_category;
        //迭代器指向的元素类型
        typedef T value_type;
        //迭代器之间的距离类型
        typedef ptrdiff_t difference_type;
        //元素指针
        typedef T* pointer;
        //引用类型
        typedef T& reference;

        //构造函数
        explicit iterator(T* thePosition=nullptr):position(thePosition) {};

        T& operator*() const {
            return *position;
        }
        //注意，本例子里是指针，但是不能保证所有的position都是指针
        T* operator->() const {
            return &*position;
        }
        //前加
        iterator& operator++() {
            ++position;
            return *this;
        }
        //后加
        iterator operator++(int) {
            iterator old=*this;
            ++ position;

            //RVO / NRVO（返回值优化）可能只会有一次拷贝构造
            //如果不能RVO，那么会优先调用移动构造函数
            return old;
        }

        iterator& operator--() {
            --position;
            return *this;
        }

        iterator operator--(int) {
            iterator old=*this;
            --position;
            return old;
        }

        bool operator!=(const iterator& rhs) const {
            return position!=rhs.position;
        }

        bool operator==(const iterator& rhs) const {
            return position==rhs.position;
        }

    protected:
        T* position;
    };

public:
    explicit arrayList(int initialCapacity=10);
    arrayList(const arrayList<T>&);
    arrayList<T>& operator=(const arrayList<T>&);
    ~arrayList() override {
        delete[] element;
    };

    //ADT方法
    [[nodiscard]] bool empty() const override {
        return listSize==0;
    }
    [[nodiscard]] int  size() const override {
        return listSize;
    }
    std::ostream& operator<<(std::ostream& out) {
        output(out);
        return out;
    }
    T& get(int index) const override;
    int indexOf(const T& element) const override;
    void erase(int index) override;
    void insert(int index, const T& element) override;
    void output(std::ostream& out) const override;

    [[nodiscard]] int capacity() const {
        return arrayLength;
    };

    iterator begin() {
        return iterator(element);
    }

    iterator end() {
        return iterator(element+listSize);
    }

     iterator begin() const {
        return iterator(element);
    }

    iterator end() const {
        return iterator(element);
    }





protected:
    void checkIndex(int index) const;
    T* element;
    int listSize;
    int arrayLength;
};

template<class T>
arrayList<T>::arrayList(int initialCapacity) {
    if (initialCapacity<1) {
        throw std::system_error(std::make_error_code(std::errc::invalid_argument));
    }
    arrayLength=initialCapacity;
    element = new T[arrayLength];
    listSize=0;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T>& list) {
    arrayLength=list.arrayLength;
    listSize=list.listSize;
    element = new T[arrayLength];
    std::copy(list.element,list.element+listSize,element);
}

template<class T>
void arrayList<T>::checkIndex(int index) const {
    if (index<0 || index>=listSize) {
 throw std::system_error(std::make_error_code(std::errc::invalid_argument));    }
}

template<class T>
T& arrayList<T>::get(int index) const {
    checkIndex(index);
    return element[index];
}

template<class T>
int arrayList<T>::indexOf(const T& e) const {
    for (int i=0;i<listSize;i++) {
        if (e==element[i]) {
            return i;
        }
    }
    return -1;
}

template<class T>
void arrayList<T>::erase(int index) {
    checkIndex(index);
    std::copy(element+index+1,element+listSize,element+index);
    element[--listSize].~T();
}

template<class T>
void arrayList<T>::insert(int index, const T& e) {
    if (index<0 || index >listSize ) {
        throw std::system_error(std::make_error_code(std::errc::invalid_argument));
    }


    // 两倍率扩容因子
    if (listSize==arrayLength) {
        changeLength1D(element,arrayLength,2*arrayLength);
        arrayLength*=2;
    }

    std::copy_backward(element+index,element+listSize,element+listSize+1);
    element[index]=e;

    listSize++;
}

template<class T>
void arrayList<T>::output(std::ostream& out) const {
    copy(element,element+listSize, std::ostream_iterator<T>(out," "));
    for (int i=0;i<listSize;i++) {
        out<<element[i]<<' ';
    }
    out<<std::endl;
}








#endif //STUDY_ALGORITHMS_ARRAYLIST_H