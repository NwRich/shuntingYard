/*A program by Nicholas Rich (with help from Raveen Karnik)
 *read an equation from a user and then put it into a tree and convert to postfix, prefix, or infix
 * 2/20/18
 */

#include <iostream>
#include <cstring>
#include <ctype.h>
#include "node.h"
#include <map>
#include <vector>

using namespace std;
void add(char* newChar);//pretty much the main function used to convert to a tree and print out all of the notations
node* goToEnd();//used to get the end of the stack 
node* getEnd();//used to get the end of the output
node* push(node* & nodeHead, char newChar);//add something to the end of a linked list
void printPost(node* nodeHead);//used to print postfix notation
void printPre(node* nodeHead);//used to print prefix notation
void printIn(node* nodeHead);//used to print infix notation
node* head;//global head that is used for the stack
node* output;//global head that is used for the output
int main () {
  cout << "put in an equation" << endl;//ask the user for input
  char* newChar = new char[32];//used to hold the users input
  cin.get(newChar,32);//write to newChar
  cin.get();//clear the buffer
  add(newChar);//call the add method
  return 0;//end
}

void add (char* newChar) {
  map<char, int> precedence;//used to set precedence for converting to postfix
  precedence['+'] = 2;
  precedence['-'] = 2;
  precedence['*'] = 3;
  precedence['/'] = 3;
  precedence['^'] = 4;
  map<char, int> assoc;//used to set associativity for converting to postfix
  assoc['^'] = 2;
  assoc['-'] = 1;
  assoc['+'] = 1;
  assoc['*'] = 1;
  assoc['/'] = 1;
  for (int i = 0; i < 16; i++) {//go throught the input
    if (newChar[i] != NULL) {//as long as the input is equal to something
      node* current = new node();//creat a new node
      current->setValue(newChar[i]);//set the value of the new node
      if(isdigit(current->getValue())) {//check to see if it is a number
	push(output, current->getValue());//push current to the output
      }
      else if(current->getValue() == '(' || current->getValue() == ')') { //if the char is a parenthesis
	if (newChar[i] == '(') {
	  push(head, current->getValue());//push to the stack
	}
	else {//else the its )
	  while (goToEnd()->getValue() != '(') {//if the stack is not a (
	    push(output, current->getValue());//push of the stack
	    node* end = goToEnd();//create a new node at the end of the stack
	    end->getPrev()->setNext(NULL);//set the end of the stacks next to null
	    delete end;//delete the end
	  }
	  node* end = goToEnd();//node at the end of the stack
	  if (end->getPrev() != NULL) {//is the previous is not null
	    end->getPrev()->setNext(NULL);//getting rid of the end
	    delete end;//delete the end
	  }
	  else {
	    head = NULL;//head is empty and the parthesis are mismatched
	  }
	}
      }
      else {//otherwise the char is an operartor
	if (head != NULL) {
	  while ((precedence[goToEnd()->getValue()] > precedence[current->getValue()]) ||
		 (precedence[goToEnd()->getValue()] == precedence[current->getValue()] &&
		assoc[goToEnd()->getValue()] == 1) && goToEnd()->getValue() != '(') {//check for asscoiativity and precedence
	    push(output, current->getValue());//push to the output
	    node* end = goToEnd();//get rid of the end node
	    if (end->getLeft() != NULL) {
	      end->getPrev()->setNext(NULL);
	      delete end;
	    }
	    else {
	      head = NULL;
	      break;
	    }
	  }
	}
	push(head, current->getValue());//otherwise add to the end of the stack
      }
    }
  }
  while (head != NULL) {//push everthing to the output
    push(output, goToEnd()->getValue());//pushing to the output
    node* end = goToEnd();//getting rid of the end node
    if (end->getPrev() != NULL) {
      end->getPrev()->setNext(NULL);
      delete end;
    }
    else {
      head = NULL;
    }
  }
  node* tree = getEnd();//node for the head of the tree
  node* current = output;//current is the same as the output head
  while (current != NULL) {//while current is not empty
    if (isdigit(current->getValue()) == 0) {//if not a digit
      current->setLeft(current->getPrev()->getPrev());//set the left as double the previous
      current->setRight(current->getPrev());//set the right as the previous
      current->setPrev(current->getLeft()->getPrev());//set the previous as lefts previous
      if (current->getPrev() != NULL) {//if previous is not null
	current->getPrev()->setNext(current);//set the prev as the next of current
      }
      current->getLeft()->setPrev(NULL);//removing current from the output list
      current->getLeft()->setNext(NULL);
      current->getRight()->setPrev(NULL);
      current->getRight()->setNext(NULL);
    }
    current = current->getNext();
  }
  cout << "do you want to print postfix, prefix, or infix notation?" << endl;//ask the user for an input
  char* input;
  cin >> input;
  cin.get();
  if (strcmp(input, "postfix") == 0) {//if the input is postfix
    printPost(tree);
  }
  if(strcmp(input, "prefix") == 0) {//if the input is prefix
    printPre(tree);
  }
  if(strcmp(input, "infix") == 0) {//if the input is infix
    printIn(tree);
  }
}
  
  
node* push (node* &nodeHead, char newChar) {//used to push to the end of a linked list
  node* newNode = new node();
  newNode->setValue(newChar);
  if (nodeHead == NULL) {
    nodeHead = newNode;
    nodeHead->setRight(NULL);
    newNode->setLeft(NULL);
  }
  else {
    node* endNode = goToEnd();
    endNode->setRight(newNode);
    newNode->setRight(NULL);
    newNode->setLeft(endNode);
  }
  return nodeHead;
}

node* goToEnd() {//goes to the end of the stack
  node* current = head;
  while (current->getRight() != NULL) {
    current = current->getRight();
    }
  return current;
}

node* getEnd() {//goes to end of the output (two different method because I had to add this later and had bad naming conventions and was lazy)
  node* current = output;
  while (current->getRight() != NULL) {
    current = current->getRight();
  }
  return current;
}

void printPre(node* nodeHead) {//print it out in prefix notation
  if (nodeHead->getRight() != NULL) {
    printPre(head->getRight());
  }
  if (nodeHead->getLeft() != NULL) {
    printPre(nodeHead->getLeft());
  }
  value.push_back(nodeHead->getValue());
}

void printIn(node* nodeHead) {//print out in infix notation
  if (nodeHead->getLeft() != NULL) {
    cout << "(";
    printIn(nodeHead->getLeft());
  }
  if (isdigit(nodeHead->getValue())) {
    cout << nodeHead->getValue();
  }
  else {
    cout << nodeHead->getValue();
  }
  if (nodeHead->getRight() != NULL) {
    printIn(head->getRight());
    cout << ")";
  }
}

void printPost(node* nodeHead) {//print out in postfix notation
  if (nodeHead->getLeft() != NULL) {
    printPost(nodeHead->getLeft());
  }
  if(nodeHead->getRight() != NULL) {
    printPost(nodeHead->getRight());
  }
  if (isdigit(nodeHead->getValue())) {
    cout << head->getValue() << " ";
  }
  else {
    cout << head->getValue() << " ";
  }
}
