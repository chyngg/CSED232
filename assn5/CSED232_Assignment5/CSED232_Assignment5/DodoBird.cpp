#include "DodoBird.h"
#include <iostream>

DodoBird::DodoBird(std::string player_name) : Bird(player_name)
{
	alive = 1;
	vote = 0;
	did_kill = 0;
	number = 6;
}

DodoBird::~DodoBird()
{
	alive = 0;
	vote = 0;
	did_kill = 0;
	number = 6;
}

void DodoBird::Skill(BirdList* birdlist)
{
	std::cout << "당신은 능력이 없는 조류입니다.\n";
}
