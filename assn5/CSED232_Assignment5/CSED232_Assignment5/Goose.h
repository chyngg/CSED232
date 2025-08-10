#pragma once
#include "Bird.h"
#include "BirdNode.h"
#include "BirdList.h"
#include <string>

class Goose :
    public Bird
{
public:
    Goose(std::string player_name);
    ~Goose();
    void Skill(BirdList* birdlist) override;
};