#include <iostream>
#include <cstring>
#include <ctype.h>
#include "node.h"
#include <map>
#include <vector>

using namespace std;
node* head;
void add(char* newChar, vector<char> &output);
void print (vector<char> output);//pass in a vector
node* goToEnd();
void debug();
node* push(node* &head, char newChar);
//node* head;
int main () {
  bool working = true;
  char* input = new char[16];
  vector<char> output;
  cout << "put in an equation" << endl;
  char* newChar = new char[32];
  cin.get(newChar,32);
  cin.get();
  add(newChar,output);
  print(output);//pass in a vector
  return 0;
}

void add (char* newChar, vector<char> &output) {
  map<char, int> precedence;
  precedence['+'] = 2;
  precedence['-'] = 2;
  precedence['*'] = 3;
  precedence['/'] = 3;
  precedence['^'] = 4;
  map<char, int> assoc;
  assoc['^'] = 2;
  assoc['-'] = 1;
  assoc['+'] = 1;
  assoc['*'] = 1;
  assoc['/'] = 1;
  for (int i = 0; i < 16; i++) {
    if (newChar[i] != NULL) {
      node* current = new node();
      current->setValue(newChar[i]);
      if(isdigit(newChar[i])) {
	output.push_back(newChar[i]);
      }
      else if(current->getValue() == '(' || current->getValue() == ')') { 
	if (newChar[i] == '(') {
	  push(head, current->getValue());//push to the stack
	}
	else {
	  while (goToEnd()->getValue() != '(' || goToEnd()->getValue() != ')') {
	    output.push_back(goToEnd()->getValue());
	    node* end = goToEnd();
	    end->getLeft()->setRight(NULL);
	    delete end;
	  }
	  node* end = goToEnd();
	  if (end->getLeft() != NULL) {
	    end->getLeft()->setRight(NULL);
	    delete end;
	  }
	  else {
	    head = NULL;
	  }
	}
      }
      else {
	if (head != NULL) {
	  while ((precedence[goToEnd()->getValue()] > precedence[current->getValue()]) ||
		 (precedence[goToEnd()->getValue()] == precedence[current->getValue()] &&
		assoc[goToEnd()->getValue()] == 1) && goToEnd()->getValue() != '(') {//check asscoiativity
	    output.push_back(goToEnd()->getValue());
	    node* end = goToEnd();
	    if (end->getLeft() != NULL) {
	      end->getLeft()->setRight(NULL);
	      delete end;
	    }
	    else {
	      head = NULL;
	      break;
	    }
	  }
	}
	push(head, current->getValue());
      }
    }
  }
  while (head != NULL) {
    output.push_back(goToEnd()->getValue());
    node* end = goToEnd();
    if (end->getLeft() != NULL) {
      end->getLeft()->setRight(NULL);
      delete end;
    }
    else {
      head = NULL;
    }
  }
}

node* push (node* &head, char newChar) {
  node* newNode = new node();
  newNode->setValue(newChar);
  if (head == NULL) {
    head = newNode;
    head->setRight(NULL);
    newNode->setLeft(NULL);
  }
  else {
    node* endNode = goToEnd();
    endNode->setRight(newNode);
    newNode->setRight(NULL);
    newNode->setLeft(endNode);
  }
  return head;
}

void print (vector<char> output) {//pass in a vector
  for (vector<char>::iterator it = output.begin(); it != output.end(); it++) {
    cout << *it;
  }
  cout << endl;
}

void debug() {
  bool working = true;
  if (working == true) {
    cout << "debug" << endl;
  }
}

node* goToEnd() {
  node* current = head;
  while (current->getRight() != NULL) {
    current = current->getRight();
    }
  return current;
}
