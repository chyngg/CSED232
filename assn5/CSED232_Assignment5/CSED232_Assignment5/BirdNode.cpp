#include "BirdNode.h"

BirdNode::BirdNode() {
	this->bird = NULL;
	this->next = NULL;
}

BirdNode::BirdNode(Bird* bird) {
	this->bird = bird;
	this->next = NULL;
}

BirdNode::~BirdNode() {
	delete this->bird;
	this->next = NULL;
}

void BirdNode::SetBird(Bird* bird) {
	this->bird = bird;
}

void BirdNode::SetNext(BirdNode* next) {
	this->next = next;
}

Bird* BirdNode::GetBird() const { // BirdNode->Bird
	return this->bird;
}

BirdNode* BirdNode::GetNext() const { // 현재 birdnode의 다음 노드 반환
	return this->next;
}