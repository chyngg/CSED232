#pragma once
#include <string>
#include "Goose.h"

class MorticianGoose : public Goose
{
public: 
	MorticianGoose(std::string player_name);
	~MorticianGoose();
	void Skill(BirdList* birdlist) override; // ¿°½À
};