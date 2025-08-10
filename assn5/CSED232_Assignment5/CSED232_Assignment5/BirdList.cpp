#include "BirdList.h"

BirdList::BirdList() {
	head = nullptr;
	tail = nullptr;
}

BirdList::~BirdList() {
	BirdNode* current = head;
	while (current != nullptr) {
		BirdNode* next = current->GetNext();
		delete current;
		current = next;
	}
	head = nullptr;
	tail = nullptr;
}

BirdNode* BirdList::GetHead() const {
	return this->head;
}

BirdNode* BirdList::GetTail() const {
	return this->tail;
}

void BirdList::AddBirdNode(BirdNode* node) {
	if (node == nullptr)
		return;

	if (this->head == nullptr) {
		head = node;
		tail = node;
	}
	else {
		tail->SetNext(node);
		tail = node;
	}


}