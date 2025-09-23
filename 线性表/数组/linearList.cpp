//
// Created by Ko-chieh Yin on 9/21/25.
//

#include "util.h"
#include "arrayList.h"
#include "multipleTable.h"
#include "vectorList.h"

void testArrayList() ;
void testIterator();
void exam();
void testVectorList() ;
void testMultipleTable();
int main(){

    // testArrayList();
    // testIterator();
    // exam();
    // testVectorList();
    testMultipleTable();

    return 0;
}


void testArrayList() {
    linearList<int> *x = new arrayList<int>();

    x->insert(0,1);
    x->insert(1,2);
    x->erase(0);
    std::cout<<x->get(0)<<std::endl;
    delete x;
}


void testIterator() {

    std::unique_ptr<arrayList<int>> x = std::make_unique<arrayList<int>>();

    x->insert(0,1);
    x->insert(1,2);

    for (const auto i: *x) {
        p(i);
    }
}

//习题部分
void exam() {
    //1.如果数组二倍扩容
    int** x= new int*[1];
    for (int i=0;i<1;i++) {
        x[i]=new int[1];
    }
    //小坑 ， x+0是右值 ，x[0]是左值
    changeLength1D(x[0],1,2);
    for (int i=0;i<1;i++) {
        delete[] x[i];
    }
    delete[] x;


}

void testVectorList() {
    vectorList<int> x = vectorList<int>();
   for (int i=0;i<11;i++) {
       x.insert(i,i);
   }

    p(x.capacity());
}

void testMultipleTable() {


    std::cout << "==== 测试 multipleTable ====" << std::endl;
    multipleTable<int> mt(10, 0.5, 3);

    mt.insert(0, 0, 1);
    mt.insert(0, 1, 2);
    mt.insert(1, 0, 100);
    mt.insert(2, 0, 200);

    std::cout << "表0: ";
    for (size_t i = 0; i < mt.size(0); i++) std::cout << mt.get(0, i) << " ";
    std::cout << std::endl;

    std::cout << "表1: ";
    for (size_t i = 0; i < mt.size(1); i++) std::cout << mt.get(1, i) << " ";
    std::cout << std::endl;

    std::cout << "表2: ";
    for (size_t i = 0; i < mt.size(2); i++) std::cout << mt.get(2, i) << " ";
    std::cout << std::endl;


}
