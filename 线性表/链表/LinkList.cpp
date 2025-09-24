//
// Created by Ko-chieh Yin on 9/24/25.
//

#include <iostream>

#include "SinglyLinkedList.h"

int main() {
    auto *list = new SinglyLinkedList<int>();
    list->insert(0,1);
    list->insert(0,2);
    list->insert(0,3);
    list->erase(0);
    list->output(std::cout);
    delete list;
    return 0;
}
