#include "Falcon.h"
#include <iostream>

Falcon::Falcon(std::string player_name) : Bird(player_name)
{
	alive = 1;
	vote = 0;
	did_kill = 0;
	number = 0;
}

Falcon::~Falcon()
{
	alive = 0;
	vote = 0;
	number = 0;
	did_kill = 0;
}

void Falcon::Skill(BirdList* birdlist) // 살조 - 송골매
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

}

