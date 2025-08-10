#pragma once
#include "Goose.h"
#include <string>

class DetectiveGoose : public Goose
{
public:
	DetectiveGoose(std::string player_name);
	~DetectiveGoose();
	void Skill(BirdList* birdlist) override; // Á¶»ç
};