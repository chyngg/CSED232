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

void Falcon::Skill(BirdList* birdlist) // ���� - �۰��
{
	std::string who_to_kill;
	std::cout << "�����ϰ� ���� �÷��̾��� �̸��� �Է��ϼ���: ";
	std::cin >> who_to_kill;

	BirdNode* current = birdlist->GetHead();

	while (current->GetBird()->GetPlayerName() != who_to_kill) {
		current = current->GetNext();
	}
	current->GetBird()->SetAlive(false);

	std::cout << "��ü �޽���: " << who_to_kill << "��(��) ������ ���ش��Ͽ����ϴ�..\n";

}

