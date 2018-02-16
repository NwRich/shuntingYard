#include "node.h"

node::node() {
  right = NULL;
  left = NULL;
  prev = NULL;
}

node::~node() {
  value = NULL;
}

void node::setValue(char newValue) {
  value = newValue;
}

void node::setRight(node* newNext) {
  right = newNext;
}

void node::setLeft(node* newPrevious) {
  left = newPrevious;
}

void node::setPrev(node* newPrev) {
  prev = newPrev;
}

node* node::getPrev() {
  return prev;
}
node* node::getRight() {
  return right;
}

node* node::getLeft() {
  return left;
}

char node::getValue() {
  return value;
}
