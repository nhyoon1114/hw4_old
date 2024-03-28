#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;

bool isEndNode(Node * root);
bool hasOneChild(Node * root);
bool hasLeftChild(Node * root);
bool hasRightChild(Node * root);

// You may add any prototypes of helper functions here
bool isEndNode(Node * root)
{
  if (root->left == nullptr && root->right == nullptr) {
    return true;
  }
  return false;
}

bool hasOneChild(Node * root)
{
  if (hasLeftChild(root) || hasRightChild(root)) {
    return true;
  }
  return false;
}

bool hasLeftChild(Node * root) 
{
  if (root->left != nullptr && root->right == nullptr) {
    return true;
  }
  return false;
}

bool hasRightChild(Node * root) 
{
  if (root->left == nullptr && root->right != nullptr) {
    return true;
  }
  return false;
}

bool equalPaths(Node * root)
{
    // Add your code below

  //root node is nullptr
  if (root == nullptr) {
    return true;
  }
  
  //root node is an end node
  if (isEndNode(root)) {
    return true;
  }

  //root node has ONE child
  if (hasOneChild(root)) {
    if (hasLeftChild(root)) {
      return equalPaths(root->left);
    }
    else {
      return equalPaths(root->right);
    }
  }

  //root node has TWO children
  else {
    //both nodes are end nodes
    if (isEndNode(root->left) && isEndNode(root->right)) {
      return true;
    }

    //only left node is an end node -> false
    else if (isEndNode(root->left)) {
      return false;
    }
    //only right node is an end node -> false
    else if (isEndNode(root->right)) {
      return false;
    }
    //both nodes have children
    else {
      return (equalPaths(root->left) && equalPaths(root->right));
    }

  }
  
  //






/*
  //root node has at least one child

  //root node has exactly one child
  if (hasOneChild(root)) {
    return 
  }

  //left node is end, right node is NOT end -> false
  else if (isEndNode(root->left) && !isEndNode(root->right)) {
    return false;
  }

  //left node is NOT end, right node is end -> false
  else if (!isEndNode(root->left) && isEndNode(root->right)) {
    return false;
  }

  //both left and right nodes are NOT end nodes
  else if (!isEndNode(root->left) && !isEndNode(root->right)) {
    return (equalPaths(root->left) && equalPaths(root->right));
  }

  //either left or right node (but not)
  else (isEndNode(root->left) || isEndNode(root->right)) {
    return false;
  }
*/
}

