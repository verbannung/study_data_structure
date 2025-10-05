//
// Created by Ko-chieh Yin on 9/23/25.
//

#ifndef STUDYALGORITHMS_VECTORLIST_H
#define STUDYALGORITHMS_VECTORLIST_H
#include <ostream>
#include <system_error>

#include "linearList.h"

// 以 std::vector 实现的线性表

template<class T>
class vectorList :public linearList<T> {

    friend std::ostream& operator<<(std::ostream& out,const vectorList<T>& x);



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
    explicit vectorList(size_t initialCapacity=10,float loadFactor=0.5);
    vectorList(const vectorList<T>&);
    vectorList<T>& operator=(const vectorList<T>&);
    ~vectorList() override =default;

    //ADT方法
    [[nodiscard]] bool empty() const override {
        return element.size()==0;
    }
    [[nodiscard]] size_t  size() const override {
        return element.size();
    }
    std::ostream& operator<<(std::ostream& out) const {
        output(out);
        return out;
    }
    const T& get(size_t index) const override;
    std::optional<size_t> indexOf(const T& element) const override;
    void erase(size_t index) override;
    void insert(size_t index, const T& element) override;
    void output(std::ostream& out) const override;

    [[nodiscard]] size_t capacity() const {
        return element.capacity();
    };

    iterator begin() {
        return iterator(element.data());
    }

    iterator end() {
        return iterator(element.data()+this->size());
    }

     iterator begin() const {
        return iterator(element.data());
    }

    iterator end() const {
        return iterator(element.data()+this->size());
    }





protected:
    void checkIndex(size_t index) const;


    std::vector<T> element;


    float loadFactor;
};

template<class T>
vectorList<T>::vectorList(size_t initialCapacity,float theLoadFactor) {
    if (initialCapacity<1) {
        throw std::system_error(std::make_error_code(std::errc::invalid_argument));
    }
    element.reserve(initialCapacity);
    loadFactor=theLoadFactor;
}

template<class T>
vectorList<T>::vectorList(const vectorList<T>& list) {
    element = std::vector<T>(list.element);
    loadFactor = list.loadFactor;
}

template<class T>
void vectorList<T>::checkIndex(const size_t index) const {
    if ( index>=size()) {
        throw std::system_error(std::make_error_code(std::errc::invalid_argument));
    }
}






template<class T>
const T &vectorList<T>::get(size_t index) const  {
    checkIndex(index);
    return element.at(index);
}

template<class T>
std::optional<size_t> vectorList<T>::indexOf(const T& e) const {
    for (size_t i=0;i<size();i++) {
        if (e==element[i]) {
            return std::optional<size_t>(i);
        }
    }
    return {};
}

template<class T>
void vectorList<T>::erase(size_t index) {
    checkIndex(index);
    element.erase(element.begin()+index);
}

template<class T>
void vectorList<T>::insert(size_t index, const T& e) {
    // if (index<0 ) {
    //     throw std::system_error(std::make_error_code(std::errc::invalid_argument));
    // }

    if (size()>= capacity()) {

        size_t newCap = std::max(static_cast<size_t>(capacity()*(1+loadFactor)),static_cast<size_t>(1));
        element.reserve(newCap);
    }

    element.insert(element.begin() + index, e);



}

template<class T>
void vectorList<T>::output(std::ostream& out) const {
    for (size_t i=0;i<size();++i) {
        out<<element[i]<<" ";
    }
    out<<std::endl;
}

template<class T>
vectorList<T>& vectorList<T>::operator = (const vectorList<T>& rhs) {
    if (this != &rhs) {
        element = rhs.element;
        loadFactor = rhs.loadFactor;
    }
    return *this;
}




#endif //STUDYALGORITHMS_VECTORLIST_H