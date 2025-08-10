#pragma once
#include "Bird.h"
#include "BirdNode.h"
#include "BirdList.h"

class BirdList;
class GGD;

class Falcon : public Bird
{
public:
	Falcon(std::string player_name);
	~Falcon();
	void Skill(BirdList* birdlist) override;
};
