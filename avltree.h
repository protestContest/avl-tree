#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include "Node.h"
#include <string>

template <typename T>
class Avltree {
 private:
  Node<T>* root;
  void traversalPrint(Node<T>* root);
  int depth;
  int widestVal;
  Node<T>* rotateRight(Node<T>* critNode);
  Node<T>* rotateLeft(Node<T>* critNode);

 public:
  Avltree<T>();
  ~Avltree<T>();

  bool find(T v);
  void remove(T v);
  void insert(T v);
  void print();
};


#endif
