#pragma once
#include "Bird.h"
#include "BirdNode.h"
#include "BirdList.h"
#include <string>

class GGD;

class DodoBird : public Bird
{
public: 
	DodoBird(std::string player_name);
	~DodoBird();
	void Skill(BirdList* birdlist) override;
};