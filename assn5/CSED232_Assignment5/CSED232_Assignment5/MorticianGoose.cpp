#include "MorticianGoose.h"
#include "Macro.h"
#include <iostream>

MorticianGoose::MorticianGoose(std::string player_name) : Goose(player_name)
{
	alive = 1;
	vote = 0;
	did_kill = 0;
	number = 4;
}

MorticianGoose::~MorticianGoose()
{
	alive = 0;
	vote = 0;
	did_kill = 0;
	number = 4;
}

void MorticianGoose::Skill(BirdList* birdlist) // 염습
{
	BirdNode* current = birdlist->GetHead();
	while (current->GetBird()->IsAlive() == 1) {
		current = current->GetNext();
		if (current == nullptr) {
			std::cout << "염습 가능 대상이 없습니다.\n";
			return;
		}
	}

	std::string who_to_search;
	std::cout << "염습하고 싶은 플레이어의 이름을 입력하세요 : ";
	std::cin >> who_to_search;


	current = birdlist->GetHead();
	while (current->GetBird()->GetPlayerName() != who_to_search) {
		current = current->GetNext();
	}
	std::cout << who_to_search << "의 역할은 " << BirdRoleName[current->GetBird()->GetNumber()] << "입니다.\n";
}