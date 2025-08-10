#include "Goose.h"
#include <iostream>

Goose::Goose(std::string player_name) : Bird(player_name)
{
	alive = 1; 
	vote = 0;
	did_kill = 0;
	number = 5;
}

Goose::~Goose() {
	alive = 0;
	vote = 0;
	did_kill = 0;
	number = 5;
}

void Goose::Skill(BirdList* birdlist) {
	std::cout << "당신은 능력이 없는 조류입니다." << std::endl;
}