#include "avltree.h"
#include <string>
using std::string;

int main() {
    Avltree<int>* a = new Avltree<int>();

    a->insert(4);
    a->insert(7);
    a->insert(6);
    a->print();

    return 0;
}
