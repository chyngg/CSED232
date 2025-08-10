#include "prob1.h"
#include <iostream>
#include <limits>

void add(OrderedList* ordered, int v) {
	Node* new_node = new Node(); // create new node
	new_node->value = v;
	new_node->next = NULL;

	Node* current = ordered->head; // node to find where to insert
	Node* previous = NULL; // points the previous node of "current" node

	if (ordered->head == NULL) { // if there is no element in the list
		ordered->head = new_node; // new node becomes the head of the list
		ordered->m_size++;
		return;
	}

	else{
		while (current != NULL && current->value < new_node->value) { // repeat until you find location to insert (according to the ascending order)
			previous = current;
			current = current->next;
		}

		if (previous == NULL) { // when we insert node in the first place
			new_node->next = ordered->head; 
			ordered->head = new_node;
		}
		else {
			previous->next = new_node;
			new_node->next = current;
		}
	} 
	ordered->m_size++;

}

void add(OrderedList* ordered, const int* arr, int size) { // take values from arr, store in the linked list
	for (int i = 0; i < size; i++) {
		add(ordered, arr[i]);
	}
}

void remove(OrderedList* ordered, int index) {
	Node* current = ordered->head; // node to find where to add
	Node* previous = current; // points the previous node of "current" node
	int cnt = 0; // count number to find location to remove

	if (cnt == index) { // when the (node to remove) is located in the first place
		if (current->next != NULL) // if there is at least two node in the list
			ordered->head = current->next; 

		else // if there is exactly one node in the list
			ordered->head = NULL;
		
		ordered->m_size--;
		delete current;
		return;
	}

	else {
		while (cnt != index) { // repeat until you find location to insert (according to the ascending order)
			previous = current;
			current = current->next;
			cnt++;
		}

		if (current->next != NULL) { 
			Node* temp = current->next;
			previous->next = temp;
		}
		else { // if the node (to remove) is located at the end of the list
			previous->next = NULL;
		}
		delete current;
		ordered->m_size--;

	}
	return;
}


int size(OrderedList* ordered) { // return the size of ordered list
	return ordered->m_size;
}

bool contains(OrderedList* ordered, int v) { // determine whether the node with value v is in the list
	Node* current = ordered->head;

	if (current == nullptr) // if the list is empty
		return false;

	if (current->value == v) //if there is exactly one node in the list
		return true;

	while (current != NULL) { // repeat searching from the first place to the end of the list
		if (current->value == v)
			return true; // if there is a node with value v

		current = current->next;
	}
	return false; // if there is no node with value v
}

int getValue(OrderedList* ordered, int idx) {
	int cnt = 0;

	if (idx >= ordered->m_size)
		return std::numeric_limits<int>::min();

	Node* current = ordered->head;
	
	while (idx != cnt) {
		current = current->next;
		cnt++;

		if (current == NULL)
			return std::numeric_limits<int>::min();
	}

	return current->value; // return the value of the node
}

