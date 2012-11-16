#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include "Node.h"
#include <string>

template <typename T>
class Avltree {
 private:
  Node<T>* root;
  void traversalPrint(Node<T>* root);
  void preorderPrint(Node<T>* root);
  int depth;
  int widestVal;
  void rotate(Node<T>** critNode, int dir);

 public:
  Avltree<T>();
  ~Avltree<T>();

  bool find(T v);
  void remove(T v);
  void insert(T v);
  void print();
  void simplePrint();
};


#endif
