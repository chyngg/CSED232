#pragma once
#include "Duck.h"

class BirdList;
class Duck;
class GGD;

class AssassinDuck : public Duck
{
private:
	int assassin_limit; // 암살 제한 횟수

public:
	AssassinDuck(std::string player_name);
	~AssassinDuck();
	void Skill(BirdList* birdlist) override; // 암살
	void Skill_2(BirdList* birdlist) override; // 살조
};