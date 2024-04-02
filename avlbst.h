#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
 Node<Key, Value>* node = BinarySearchTree<Key, Value>::root_;

    while (true) {
        if (node == NULL) {
          Node<Key, Value>* newNode = new Node<Key, Value>(new_item.first, new_item.second, NULL);
          BinarySearchTree<Key, Value>::root_ = newNode;
          return;
        }

        else if (node->getKey() == new_item.first) {
            node->setValue(new_item.second);
            return;
        }
        else if (new_item.first < node->getKey()) {
            if (node->getLeft() == NULL) {
                Node<Key, Value>* newNode = new Node<Key, Value>(new_item.first, new_item.second, node);
                node->setLeft(newNode);
                return;
            }
            node = node->getLeft();
        }
        else if (new_item.first > node->getKey()) {
            if (node->getRight() == NULL) {
                Node<Key, Value>* newNode = new Node<Key, Value>(new_item.first, new_item.second, node);
                node->setRight(newNode);
                return;
            }
            node = node->getRight();
        }
    }    
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    /*AVLNode<Key, Value>* node = BinarySearchTree<Key, Value>::root_;
    while (true) {
        if (node == NULL) {
          return;
        }
        else if (key == node->getKey()) {
            //case 0: 0 children
            if (node->getLeft() == NULL && node->getRight() == NULL) {
              if (node->getParent() != NULL) {
                if (node->getParent()->getLeft() == node) {
                  node->getParent()->setLeft(NULL);
                  node->setParent(NULL);
                }
                else {
                  node->getParent()->setRight(NULL);
                  node->setParent(NULL);
                }
              }
              else {
                node = NULL;
              }
              //delete node;
            }
            //case 1: 1 child
            else if (node->getLeft() != NULL && node->getRight() == NULL) {
              //node->getLeft()->setParent(node->getParent());
              if (node->getParent() != NULL) {
                if (node->getLeft()->getKey() > node->getParent()->getKey()) {
                  //std::cout << "in R-L " << std::endl;
                  node->getParent()->setRight(node->getLeft());
                  node->getLeft()->setParent(node->getParent());
                }
                else {
                  //std::cout << "in L-L " << std::endl;
                  node->getParent()->setLeft(node->getLeft());
                  node->getLeft()->setParent(node->getParent());
                }        
                //delete node;
                //node->setParent(NULL);
                //node->setLeft(NULL);        
              }
            }
            else if (node->getLeft() == NULL && node->getRight() != NULL) {
              //node->getRight()->setParent(node->getParent());
              if (node->getParent() != NULL) {
                if (node->getRight()->getKey() < node->getParent()->getKey()) {
                  //std::cout << "in L-R " << std::endl;
                  node->getParent()->setLeft(node->getRight());
                  node->getRight()->setParent(node->getParent());
                }
                else {
                  //std::cout << "in R-R " << std::endl;
                  node->getParent()->setRight(node->getRight());
                  node->getRight()->setParent(node->getParent());
                }
                //delete node;
                
                //node->setParent(NULL);
                //node->setRight(NULL);
              }   
            }
            //case 2: 2 children
            else {
              AVLNode<Key, Value>* preNode = BinarySearchTree<Key, Value>::predecessor(node);
              //swap with predecessor
              nodeSwap(node, preNode);
              if (node->getParent()->getLeft() == node) {
                node->getParent()->setLeft(NULL);
                node->setParent(NULL);
              }
              else {
                node->getParent()->setRight(NULL);
                node->setParent(NULL);
              }
              //delete node;
            }
          //delete node;
          return;
        }
        else if (key < node->getKey()) {
            if (node->getLeft() == NULL) {
                return;
            }
            node = node->getLeft();
        }
        else if (key > node->getKey()) {
            if (node->getRight() == NULL) {
                return;
            }
            node = node->getRight();
        }
    }*/
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
