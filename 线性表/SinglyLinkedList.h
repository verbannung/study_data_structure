//
// Created by Ko-chieh Yin on 9/24/25.
//

#ifndef STUDYALGORITHMS_SINGLYLINKEDLIST_H
#define STUDYALGORITHMS_SINGLYLINKEDLIST_H

#include <ostream>

#include "linearList.h"

template<class T>
struct chainNode {
    T element;
    chainNode<T> *next;

    chainNode():element(),next(nullptr){};
    explicit chainNode(const T& e,chainNode<T> *n=nullptr):element(e),next(n){};

    chainNode(const chainNode<T>& other):element(other.element),next(nullptr){
        if (other.next!=nullptr) {
            //递归调用
            next = new chainNode<T>(*other.next);
        }
    };
    ~chainNode() {
        delete next;
    }
};

template<class T>
class SinglyLinkedList :public linearList<T> {
public:
    explicit SinglyLinkedList(int initialCapacity=10);
    SinglyLinkedList(const SinglyLinkedList<T>&);
    ~SinglyLinkedList() override;


     [[nodiscard]] bool empty() const override;
     [[nodiscard]] size_t size() const override ;

    const T& get(size_t index) const override;
     std::optional<size_t> indexOf(const T& element) const override;
     void erase(size_t index) override;
     void insert(size_t index, const T& element) override;
     void output(std::ostream& ) const override;

protected:
    void checkIndex(size_t theIndex) const;
    chainNode<T> *head;
    //链表长度
    size_t listSize;
};

template<class T>
SinglyLinkedList<T>::SinglyLinkedList(int initialCapacity):listSize(0),head(nullptr) {
    if (initialCapacity<1) {
        throw std::runtime_error("错误");
    }
}

template<class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T> & other):listSize(other.listSize),head(new chainNode<T>(*other.head)) {
}

template<class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    delete head;
    // while (head!= nullptr) {
    //     auto nextNode = head->next;
    //     delete head;
    //     head = nextNode;
    // }
}

template<class T>
bool SinglyLinkedList<T>::empty() const {
    return listSize==0;
}

template<class T>
size_t SinglyLinkedList<T>::size() const{
    return listSize;
}

template<class T>
const T& SinglyLinkedList<T>::get(const size_t index) const {
    checkIndex(index);
    auto p = head;
    for (size_t i = 0; i < index; i++) {
        p = p->next;
    }
    return p->element;
}

template<class T>
std::optional<size_t> SinglyLinkedList<T>::indexOf(const T &element) const {
    auto node = head;
    size_t index = 0;
    while (node !=nullptr) {
        if (node->element == element) {
            return index;
        }
        node = node->next;
        index++;
    }
    return {};
}

template<class T>
void SinglyLinkedList<T>::erase(size_t index) {
    checkIndex(index);
    if (index == 0) {
        auto nextNode = head->next;
        head->next = nullptr;
        delete head;
        head = nextNode;
    }else {
        auto pre = head;
        for (size_t i=0;i<index-1;i++) {
            pre = pre->next;
        }
        auto next = pre->next->next;
        pre->next->next = nullptr;
        delete pre->next;
        pre->next = next;
    }
}

template<class T>
void SinglyLinkedList<T>::insert(size_t index, const T &element) {
    if ( index>listSize) {
        throw std::out_of_range("索引非法");
    }
    if (index==0) {
        auto newHead = new chainNode<T>{element};
        newHead->next = head;
        head = newHead;
    }else {
        auto newChainNode = new chainNode<T>{element};
        auto pre = head;
        for (size_t i=0;i<index-1;i++) {
            pre = pre->next;
        }
        auto next = pre->next;
        pre->next = newChainNode;
        newChainNode->next = next;
    }
    listSize++;

}

template<class T>
void SinglyLinkedList<T>::output(std::ostream &out)  const{
    auto node = head;
    while (node!=nullptr) {
        out<<node->element<<" ";
        node = node->next;
    }
    out<<std::endl;
}

template<class T>
void SinglyLinkedList<T>::checkIndex(size_t theIndex) const {
    if ( theIndex>=listSize) {
        throw std::out_of_range("索引非法");
    }
}

#endif //STUDYALGORITHMS_SINGLYLINKEDLIST_H
