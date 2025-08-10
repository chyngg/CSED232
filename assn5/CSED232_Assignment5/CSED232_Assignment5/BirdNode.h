#pragma once
#include "Bird.h"

class Bird;
class BirdList;

class BirdNode {
private:
	Bird* bird;
	BirdNode* next;
public:
	// Default constructor
	BirdNode();
	// Constructor with parameter for the member variable bird
	BirdNode(Bird*);
	// Destructor (delete the member variable bird)
	~BirdNode();

	// Set the member variable bird to the parameter
	void SetBird(Bird*);
	// Set the member variable next to the parameter
	void SetNext(BirdNode*);
	// Get the member variable bird
	Bird* GetBird() const;
	// Get the member variable next
	BirdNode* GetNext() const;
};