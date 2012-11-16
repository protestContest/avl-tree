#include "avltree.h"
#include <cmath>
#include <list>
#include <vector>
#include <iostream>
#include <sstream>
#include "assert.h"
using std::list;
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

template <typename T>
Avltree<T>::Avltree() {
  root = 0;
  depth = 0;
  widestVal = 0;
}

template <typename T>
Avltree<T>::~Avltree() {
  
}


template <typename T>
bool Avltree<T>::find(T v) {
  Node<T>* temp = new Node<T>(v);
  root = temp;  
  return true;
}

template <typename T>
void Avltree<T>::insert(T v) {
    cout << "inserting " << v << endl;
    if (root == 0) {
        root = new Node<T>(v);
    }

    Node<T>* insertNode = new Node<T>(v);
    vector< Node<T>* >* path = new vector< Node<T>* >();
    path->push_back(root);
    Node<T>* critNode = 0;

    Node<T>** curNode = &root;
    while (*curNode != 0 && (*curNode)->getValue() != v) {
        if ((*curNode)->getBalance() != 0) {
            critNode = *curNode;
        }
        if (v < (*curNode)->getValue()) {
            curNode = &(*curNode)->getLeftChild();
        } else {
            curNode = &(*curNode)->getRightChild();
        }
    }

    if (*curNode != 0) {
        Node<T>* oldNode = *curNode;
        insertNode->setLeftChild(oldNode->getLeftChild());
        insertNode->setRightChild(oldNode->getRightChild());
        *curNode = insertNode;
        delete oldNode;
        return;
    }

    *curNode = insertNode;


    Node<T>* r = insertNode;
    // no critical node
    if (critNode == 0) {
        r = root;
    } else {
        Node<T>* critChild = 0;
        int critChildDir = 0;
        if (v < critNode->getValue()) {
            critChild = critNode->getLeftChild();
            critChildDir = -1;
        } else {
            critChild = critNode->getRightChild();
            critChildDir = 1;
        }

        // no rotation
        if (critNode->getBalance() != critChildDir) {
            critNode->setBalance(0);
            r = insertNode;
        } else {
            Node<T>* critGC = 0;
            int critGCDir = 0;
            if (v < critChild->getValue()) {
                critGC = critChild->getLeftChild();
                critGCDir = -1;
            } else {
                critGC = critChild->getRightChild();
                critGCDir = 1;
            }

            // single rotation
            if (critGCDir == critChildDir) {
                cout << "single rotation" << endl;
                critNode->setBalance(0);
                r = critGC;
                rotate(critNode, -critChildDir);
            }
            // double rotation
            else {
                cout << "double rotation" << endl;
                int rDir;
                if (v < critGC->getValue()) {
                    r = critGC->getLeftChild();
                    rDir = -1;
                } else {
                    r = critGC->getRightChild();
                    rDir = 1;
                }

                if (rDir == critGCDir) {
                    critNode->setBalance(0);
                    critChild->setBalance(critChildDir);
                } else if (rDir == -critGCDir) {
                    critNode->setBalance(critGCDir);
                } else {
                    critNode->setBalance(0);
                }
                
                // what if critNode == root?
                rotate(critChild, -critGCDir);
                rotate(critNode, -critChildDir);
            }

        }
    }

    while (r != 0 && r->getValue() != v) {
        if (v < r->getValue()) {
            r->setBalance(-1);
            r = r->getLeftChild();
        } else {
            r->setBalance(1);
            r = r->getRightChild();
        }
    }
    delete path;

}

template <typename T>
void Avltree<T>::remove(T v) {
    Node<T>** cur = &root;
    while (*cur != 0 && (*cur)->getValue() != v) {
        if (v < (*cur)->getValue()) {
            Node<T>* temp = (*cur)->getLeftChild();
            cur = &temp;
        }
        else if (v > (*cur)->getValue()) {
            Node<T>* temp = (*cur)->getRightChild();
            cur = &temp;
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

    iop->setRightChild((*cur)->getRightChild());
    *cur = (*cur)->getLeftChild();
    
    delete deleteMe;
}

template <typename T>
void Avltree<T>::simplePrint() {
    cout << root->getValue() << endl;
}

template <typename T>
void Avltree<T>::print() {
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
void Avltree<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << ", ";
    traversalPrint(root->getRightChild());
  }
}

template <typename T>
void Avltree<T>::preorderPrint(Node<T>* root) {
  if(root != 0) {
    std::cout << root->getValue() << ", ";
    traversalPrint(root->getLeftChild());
    traversalPrint(root->getRightChild());
  }
}

template <typename T>
void Avltree<T>::rotate(Node<T>*& critNode, int dir) {
    cout << critNode << endl;
    if (dir == -1) {
        cout << "rotating left" << endl;
        Node<T>*& rightChild = critNode->getRightChild();
        Node<T>*& rightLC = rightChild->getLeftChild();
        rightChild->setLeftChild(critNode);
        critNode->setRightChild(rightLC);
    } else if (dir == 1) {
        cout << "rotating right" << endl;
        Node<T>*& leftChild = critNode->getLeftChild();
        Node<T>*& leftRC = leftChild->getRightChild();
        leftChild->setRightChild(critNode);
        critNode->setLeftChild(leftRC);
    }

}

template class Avltree<int>;
template class Avltree<double>;
template class Avltree<std::string>;
