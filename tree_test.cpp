#include "BST.h"
#include <string>
using std::string;

int main() {
  BST<int>* bst = new BST<int>();


  bst->insert(5);
  bst->insert(8);
  bst->insert(3);
  bst->insert(9);
  bst->insert(12);
  bst->insert(7);
  bst->insert(2);
  bst->insert(1);
  bst->insert(6);

  bst->print();

  bst->remove(8);
  bst->print();

  bst->insert(4);
  bst->remove(5);
  bst->print();

    BST<string>* sbst = new BST<string>();
    sbst->insert("hey");
    sbst->insert("Hello");
    sbst->insert("World!");
    sbst->print();
}
