#include "avltree.h"
#include <string>
using std::string;

int main() {
    Avltree<int>* a = new Avltree<int>();

    a->insert(5);
    a->simplePrint();
    a->insert(7);
    a->simplePrint();
    a->insert(6);
    a->simplePrint();

    return 0;
}
