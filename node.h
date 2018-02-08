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
  node* getRight();
  node* getLeft();
  char getValue();
 private:
  char value;
  node* next;
  node* previous;
};
#endif
