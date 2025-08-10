#include "DetectiveGoose.h"
#include <iostream>

DetectiveGoose::DetectiveGoose(std::string player_name) : Goose(player_name)
{
	alive = 1;
	vote = 0;
	did_kill = 0;
	number = 3;
}

DetectiveGoose::~DetectiveGoose()
{
	alive = 0;
	vote = 0;
	did_kill = 0;
	number = 3;
}

void DetectiveGoose::Skill(BirdList* birdlist) // 조사
{
	std::string who_to_survey;
	std::cout << "조사하고 싶은 플레이어의 이름을 입력하세요: ";
	std::cin >> who_to_survey;

	BirdNode* current = birdlist->GetHead();
	while (current->GetBird()->GetPlayerName() != who_to_survey)
		current = current->GetNext();

	if (current->GetBird()->Num_kill() == 1)
		std::cout << who_to_survey << "은(는) 이번 라운드에 누군가를 무참히 살해하였습니다..!\n";

	else
		std::cout << who_to_survey << "은(는) 이번 라운드에 아무도 해치지 않았습니다.\n";
}

