#include "node.h"

node::node() {
  next = NULL;
  previous = NULL;
}

node::~node() {
  delete &value;
  next = NULL;
  previous = NULL;
}

void node::setValue(char newValue) {
  value = newValue;
}

void node::setRight(node* newNext) {
  next = newNext;
}

void node::setLeft(node* newPrevious) {
  previous = newPrevious;
}

node* node::getRight() {
  return next;
}

node* node::getLeft() {
  return previous;
}

char node::getValue() {
  return value;
}
