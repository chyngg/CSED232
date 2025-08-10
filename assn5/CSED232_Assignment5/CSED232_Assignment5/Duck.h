#pragma once
#include "Bird.h"
#include "BirdNode.h"
#include "BirdList.h"
#include <string>

class GGD;
class BirdList;

class Duck :
    public Bird
{
public:
    Duck(std::string player_name);
    ~Duck();
    void Skill(BirdList* birdlist) override; // ªÏ¡∂
};
