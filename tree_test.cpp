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

    a->remove(1);
    a->simplePrint();

    return 0;
}
