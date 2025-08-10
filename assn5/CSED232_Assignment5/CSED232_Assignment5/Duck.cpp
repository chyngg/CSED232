#include "Duck.h"
#include <iostream>

Duck::Duck(std::string player_name) : Bird(player_name)
{
	alive = 1;
	vote = 0;
	did_kill = 0;
	number = 2;
}

Duck::~Duck()
{
	alive = 0;
	vote = 0;
	did_kill = 0;
	number = 2;
}

void Duck::Skill(BirdList* birdlist) // 살조
{
	std::string who_to_kill;
	std::cout << "살해하고 싶은 플레이어의 이름을 입력하세요: ";
	std::cin >> who_to_kill;

	BirdNode* current = birdlist->GetHead();

	while (current->GetBird()->GetPlayerName() != who_to_kill) {
		current = current->GetNext();
	}
	current->GetBird()->SetAlive(false);

	std::cout << "전체 메시지: " << who_to_kill << "이(가) 무참히 살해당하였습니다..\n";
	
	this->did_kill = 1;

}

