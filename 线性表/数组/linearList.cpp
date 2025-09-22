//
// Created by Ko-chieh Yin on 9/21/25.
//

#include "util.h"
#include "arrayList.h"


void testArrayList() ;
void testIterator();
void exam();
int main(){

    // testArrayList();
    // testIterator();
    exam();


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
