#include "avltree.h"
#include <string>
using std::string;

int main() {
    Avltree<int>* a = new Avltree<int>();

    a->insert(1);
    a->simplePrint();
    a->insert(6);
    a->simplePrint();
    a->insert(7);
    a->simplePrint();
    a->insert(2);
    a->simplePrint();
    a->insert(8);
    a->insert(9);

    return 0;
}
