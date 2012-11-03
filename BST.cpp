#include "BST.h"
#include <cmath>
#include <list>
#include <vector>
#include <iostream>
#include <sstream>
using std::list;
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

template <typename T>
BST<T>::BST() {
  root = 0;
  depth = 0;
  widestVal = 0;
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
  
    std::stringstream getLen;
    getLen << v;
    int length = getLen.str().length();
    if (length > widestVal) {
        widestVal = length;
    }
}

template <typename T>
void BST<T>::remove(T v) {
    Node<T>** cur = &root;
    while (*cur != 0 && (*cur)->getValue() != v) {
        if (v < (*cur)->getValue()) {
            cur = &((*cur)->getLeftChild());
        }
        else if (v > (*cur)->getValue()) {
            cur = &((*cur)->getRightChild());
        }
    }
    if (*cur == 0) return;
    Node<T>* deleteMe = *cur;

    Node<T>* iop = (*cur)->getLeftChild();
    if (iop == 0) {
        *cur = (*cur)->getRightChild();
        delete deleteMe;
        return;
    }

    while (iop->getRightChild() != 0) {
        iop = iop->getRightChild();
        ++depth;
    }

    iop->setRightChild(*(*cur)->getRightChild());
    *cur = (*cur)->getLeftChild();
    
    delete deleteMe;
}

template <typename T>
void BST<T>::print() {
    int valSize = widestVal;
    list< Node<T>* >* frontier = new list< Node<T>* >();
    frontier->push_back(root);

    // for each level
    for (int level = 0; level < depth; ++level) {
        int numNodes = pow(2, level);
        int nodePreSpace = valSize * pow(2, depth - level - 1) - 1;
        int nodePostSpace = valSize * pow(2, depth - level - 1);

        // for each node in that level
        for (int n = 0; n < numNodes; ++n) {
            Node<T>* curNode = frontier->front();
            frontier->pop_front();

            for (int i = 0; i < nodePreSpace; ++i) {
                cout << " ";
            }

            if (curNode != 0) {
                std::stringstream getLen;
                getLen << curNode->getValue();
                int length = getLen.str().length();
                nodePostSpace = nodePostSpace - (length - 1);
                cout << curNode->getValue();
                frontier->push_back(curNode->getLeftChild());
                frontier->push_back(curNode->getRightChild());
            }
            else {
                cout << "X";
                frontier->push_back(0);
                frontier->push_back(0);
            }

            for (int i = 0; i < nodePostSpace; ++i) {
                cout << " ";
            }
        }

        if (level < depth - 1) {
            cout << endl;
            int nodeSpace = valSize * pow(2, depth - level - 1);
            int bSlashPreSpace = floor(0.25*(nodeSpace - 1));
            int bSlashPostSpace = nodeSpace - bSlashPreSpace - 1;
            int fSlashPostSpace = bSlashPreSpace + 1;
            int fSlashPreSpace = nodeSpace - fSlashPostSpace - 1;

            bool fSlash = true;
            for (int n = 0; n < numNodes*2; ++n) {
                if (fSlash) {
                    for (int i = 0; i < fSlashPreSpace; ++i) {
                        cout << " ";
                    }
                    cout << "/";
                    for (int i = 0; i < fSlashPostSpace; ++i) {
                        cout << " ";
                    }
                }
                else if (!fSlash) {
                    for (int i = 0; i < bSlashPreSpace; ++i) {
                        cout << " ";
                    }
                    cout << "\\";
                    for (int i = 0; i < bSlashPostSpace; ++i) {
                        cout << " ";
                    }
                }
                fSlash = !fSlash;
            }
        }

        cout << endl;
    }
    cout << endl;
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
