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
	std::cout << "����� �ɷ��� ���� �����Դϴ�." << std::endl;
}