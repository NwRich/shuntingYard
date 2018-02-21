#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

class node {
 public:
  node();
  ~node();
  void setValue(char);
  void setRight(node*);
  void setLeft(node*);
  void setPrev(node*);
  void setNext(node*);
  node* getPrev();
  node* getNext();
  node* getRight();
  node* getLeft();
  char getValue();
 private:
  char value;
  node* right;
  node* left;
  node* prev;
  node* next;
};
#endif
