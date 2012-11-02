#include "BST.h"
#include <cmath>
#include <list>
#include <iostream>
#include <sstream>
using std::list;
using std::cout;
using std::endl;
using std::stringstream;

template <typename T>
BST<T>::BST() {
  root = 0;
  depth = 0;
}

template <typename T>
BST<T>::~BST() {
  
}


template <typename T>
bool BST<T>::find(T v) {
  Node<T>* temp = new Node<T>(v);
  root = temp;  
  return true;
}

template <typename T>
void BST<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>** curr = &root;
  int curDepth = 1;

  while (*curr != 0) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    }
    ++curDepth;
  }
  *curr = temp;

  if (curDepth > depth) {
    depth = curDepth;
  }
}

template <typename T>
void BST<T>::remove(T v) {
  Node<T>* temp = new Node<T>(v);
  root = temp;
}

//template <typename T>
//void BST<T>::print() {
//  traversalPrint(root);
//}
template <typename T>
void BST<T>::print() {
    list< Node<T>* >* frontier = new list< Node<T>* >();
    frontier->push_back(root);
    int level = 0;
    int curLevelNodes = 0;
    int levelNodes, nodeSpace, nodePreSpace, nodePostSpace, fSlashPostSpace, fSlashPreSpace, bSlashPreSpace, bSlashPostSpace;
    //int fSlashPreSpace, fSlashPostSpace, bSlashPreSpace,
        //bSlashPostSpace;
    stringstream nodeString;
    
//    cout << "DEPTH: " << depth << endl << endl;

    int k = 0;
    while (frontier->empty() == false) {
    //for (int k = 0; k < pow(2, depth); ++k) {

        if (curLevelNodes == 0) {
            levelNodes = pow(2, level);
            nodeSpace = pow(2, depth - level);
            nodePreSpace = pow(2, depth - level - 1) - 1;
            nodePostSpace = pow(2, depth - level - 1);
            fSlashPostSpace = ceil(nodePostSpace / 2.0);
            fSlashPreSpace = nodeSpace - fSlashPostSpace - 1;
            bSlashPreSpace = floor(nodePreSpace / 2.0);
            bSlashPostSpace = nodeSpace - bSlashPreSpace - 1;
/*
            cout << "nodeSpace: " << nodeSpace << endl;
            cout << "nodePreSpace: " << nodePreSpace << endl;
            cout << "nodePostSpace: " << nodePostSpace << endl;
            cout << "fSlashPostSpace: " << fSlashPostSpace << endl;
            cout << "fSlashPreSpace: " << fSlashPreSpace << endl;
            cout << "bSlashPreSpace: " << bSlashPreSpace << endl;
            cout << "bSlashPostSpace: " << bSlashPostSpace << endl << endl;
*/
            if (k > 0) {
                bool fSlash = true;
                for (int i = 0; i < levelNodes; ++i) {
                    if (fSlash) {
                        for (int j = 0; j < fSlashPreSpace; ++j) {
                            nodeString << " ";
                        }
                        nodeString << "/";
                        for (int j = 0; j < fSlashPostSpace; ++j) {
                            nodeString << " ";
                        }
                    } else {
                        for (int j = 0; j < bSlashPreSpace; ++j) {
                            nodeString << " ";
                        }
                        nodeString << "\\";
                        for (int j = 0; j < bSlashPostSpace; ++j) {
                            nodeString << " ";
                        }
                    }
                    fSlash = !fSlash;
                }
                nodeString << endl;
            }
        }

        for (int i = 0; i < nodePreSpace; ++i) {
            nodeString << " ";
        }

        Node<T>* curNode = frontier->front();
        frontier->pop_front();
        if (curNode != 0) {
            frontier->push_back(curNode->getLeftChild());
            frontier->push_back(curNode->getRightChild());
            nodeString << curNode->getValue();
        }
        else {
            nodeString << "X";
        }

        for (int i = 0; i < nodePostSpace; ++i) {
            nodeString << " ";
        }
        ++curLevelNodes;
        if (curLevelNodes == levelNodes) {
            nodeString << endl;

            if (level < depth) {
            }

            curLevelNodes = 0;
            ++level;
        }
        ++k;

    }
    cout << nodeString.str() << endl;
}

template <typename T>
void BST<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    traversalPrint(root->getRightChild());
  }
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
