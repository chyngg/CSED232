#pragma once
#include "BirdNode.h"
#include <string>

class BirdNode;

class BirdList
{
private:
	BirdNode* head;
	BirdNode* tail;
public:
	BirdList();
	~BirdList();

	BirdNode* GetHead() const;
	BirdNode* GetTail() const;
	void AddBirdNode(BirdNode* node);
};

