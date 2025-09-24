//
// Created by Ko-chieh Yin on 9/24/25.
//

#ifndef STUDYALGORITHMS_LINEARLIST_H
#define STUDYALGORITHMS_LINEARLIST_H
#include <cstddef>
#include <optional>
using namespace std;

template<class T>
class LinearList{
public:
    virtual ~LinearList()= default;
    virtual bool empty() const = 0;
    virtual size_t size() const =0 ;
    virtual const T& get(size_t index) const =0;
    virtual  optional<size_t> indexOf(const T& element) const =0;
    virtual void erase(size_t index) =0;
    virtual void insert(size_t index, const T& element) =0;
    virtual void output(std::ostream& out) const =0;
};


#endif //STUDYALGORITHMS_LINEARLIST_H