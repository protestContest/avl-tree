#include "avltree.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

int main() {
    Avltree<int>* a = new Avltree<int>();

    a->insert(1);
    a->insert(3);
    a->insert(5);
    a->insert(7);
    a->insert(6);
    a->insert(4);
    a->insert(2);
    a->insert(12);
    a->simplePrint();

    cout << "-------------" << endl;

    a->remove(4);
    a->remove(7);
    a->remove(12);
    a->remove(6);
    a->simplePrint();

    delete a;

    cout << "================" << endl;

    Avltree<double>* b = new Avltree<double>();

    b->insert(1);
    b->insert(2);
    b->insert(3);
    b->insert(9);
    b->insert(8);
    b->insert(5);
    b->simplePrint();
    b->insert(4);
    b->simplePrint();
    b->insert(7);
    b->simplePrint();
    b->insert(6);
    b->simplePrint();



    return 0;
}
