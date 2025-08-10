#include "AssassinDuck.h"
#include <iostream>

AssassinDuck::AssassinDuck(std::string player_name) : Duck(player_name)
{
	alive = 1;
	vote = 0;
	did_kill = 0;
	number = 1;
	assassin_limit = 2;
}

AssassinDuck::~AssassinDuck()
{
	alive = 0;
	vote = 0;
	did_kill = 0;
	number = 1;
	assassin_limit = 0;
}

void AssassinDuck::Skill(BirdList* birdlist) // 암살
{
	if (assassin_limit == 0) // 암살 제한 횟수 도달 시
	{
		std::cout << "더 이상 암살 능력을 사용할 수 없습니다!\n";
		return;
	}

	std::string who_to_kill;
	int player_num;
	std::cout << "암살하고 싶은 플레이어의 이름을 입력하세요: ";
	std::cin >> who_to_kill;
	std::cout << "암살하고 싶은 플레이어의 역할 번호를 입력하세요: ";
	std::cin >> player_num;

	BirdNode* current = nullptr;
	current = birdlist->GetHead();
	while (current->GetBird()->GetPlayerName() != who_to_kill)
		current = current->GetNext();

	if (current->GetBird()->GetNumber() == player_num) // 플레이어의 역할 번호를 맞췄을 때
	{
		std::cout << "전체 메시지: " << who_to_kill << "이(가) 무참히 살해당하였습니다..\n";
		current->GetBird()->SetAlive(false);
		this->assassin_limit--;
		this->did_kill = 1;
	}

	else // 역할 번호를 못 맞췄을 때
	{
		std::cout << "전체 메시지: " << player_name << "은(는) 극단적 선택을 하였습니다.\n";
		this->alive = 0;
	}
	
}

void AssassinDuck::Skill_2(BirdList* birdlist) // 살조
{
	Duck::Skill(birdlist); // Duck 클래스의 Skill과 기능이 같음(살조)
}
