#pragma once
#include <iostream>
#include <limits>
using namespace std;

struct Node {
	int value; // integer value stored in the node
	Node * next; // node that points the next node in linked list
};

struct OrderedList {
	int m_size; // size of list
	Node* head; // first node in linked list

};

void add(OrderedList* ordered, int v);
void add(OrderedList* ordered, const int* arr, int size);
void remove(OrderedList* ordered, int index);
int size(OrderedList* ordered);
bool contains(OrderedList* ordered, int v);
int getValue(OrderedList* ordered, int idx);
