#include <iostream>
#include <cstring>
#include <ctype.h>
#include "node.h"
#include <map>
#include <vector>

using namespace std;
void add(char* newChar, vector<char> &output);
void print (vector<char> output);//pass in a vector
node* goToEnd();
void debug();
node* head;
int main () {
  bool working = true;
  char* input = new char[16];
  vector<char> output;
  while (working == true) {
    cout << "add, list, quit" << endl;
    cin >> input;
    cin.get();
    if (strcmp(input, "add") == 0) {
      char* newChar = new char[32];
      cin.get(newChar,32);
      cin.get();
      add(newChar,output);
    }
    if (strcmp(input, "list") == 0) {
      print(output);//pass in a vector
    }
    if (strcmp(input, "quit") == 0) {
      working = false;
    }
  }
  return 0;
}
void add (char* newChar, vector<char> &output) {
  map<char, int> precedence;
  precedence['+'] = 2;
  precedence['-'] = 2;
  precedence['*'] = 3;
  precedence['/'] = 3;
  precedence['^'] = 4;
  for (int i = 0; i < 16; i++) {
    if(isdigit(newChar[i])) {
      output.push_back(newChar[i]);
    }
    if (isdigit(newChar[i]) == false) {
      debug();
      if (head->getValue() == NULL) {
	debug();
	head->setValue(newChar[i]);
	debug();
      }
      else if (head->getValue() != NULL) {
	node* current;
	current->setValue(newChar[i]);
	if (precedence[current->getValue()] >= precedence[newChar[i]] && newChar[i] != '(') {
	  node* setOut = new node();
	  setOut->setValue(newChar[i]);
	  current->setRight(setOut);
	  current->setPrev(goToEnd());
	  goToEnd()->setRight(current);
	}
	else if (newChar[i] == '(') {
	  current = goToEnd();
	  node* newNode = new node();
	  newNode->setValue(newChar[i]);
	  current->setRight(newNode);
	}
	else if (newChar[i] == ')') {
	  current = goToEnd();
	  while (current->getValue() != '(') {
	    output.push_back(current->getValue());
	    current = current->getLeft();
	  }
	  //pop out the left bracket and get rid of the right bracket
	}
      }   
    }    
  }
  while (head->getRight() != NULL) {
    debug();
    node* end;
    end = goToEnd();
    output.push_back(end->getValue());
    node* remove;
    if(head != end) {
      remove = head;
      while (remove->getRight() != end) {
	remove = remove->getRight();
      }
      remove->setRight(NULL);
    }
  }
  // if (head->getRight() == NULL) {
  cout << head->getValue() << endl;
    output.push_back(head->getValue());
    //}
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
