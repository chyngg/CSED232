#pragma once
#include "Duck.h"

class BirdList;
class Duck;
class GGD;

class AssassinDuck : public Duck
{
private:
	int assassin_limit; // �ϻ� ���� Ƚ��

public:
	AssassinDuck(std::string player_name);
	~AssassinDuck();
	void Skill(BirdList* birdlist) override; // �ϻ�
	void Skill_2(BirdList* birdlist) override; // ����
};