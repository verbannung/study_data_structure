//
// Created by Ko-chieh Yin on 9/21/25.
//

#ifndef STUDY_ALGORITHMS_LINEARLIST_H
#define STUDY_ALGORITHMS_LINEARLIST_H
#include <algorithm>
#include <exception>
#include <iosfwd>

template<class T>
class linearList{
public:
    virtual ~linearList()= default;
    virtual bool empty() const = 0;
    virtual int size() const =0 ;
    virtual T& get(int index) const =0;
    virtual  int indexOf(const T& element) const =0;
    virtual void erase(int index) =0;
    virtual void insert(int index, const T& element) =0;
    virtual void output(std::ostream& out) const =0;
};


//二倍扩容
// 如果说是每一次都需要扩展的话，那么就需要O(n^2)的时间复杂度,空间复杂度是O(n)
//如果说是每一次扩展两倍，那么仅仅需要O(n)的时间复杂度,是空间复杂度是O(n)
template<class T>
void changeLength1D(T*& a,int oldLength,int newLength) {
    if (newLength<0)
        throw std::exception();

    T* temp = new T[newLength];
    int number = std::min(oldLength,newLength);
    // 调用拷贝赋值
    std::copy(a,a+number,temp);
    delete[] a;
    a=temp;
}





#endif //STUDY_ALGORITHMS_LINEARLIST_H