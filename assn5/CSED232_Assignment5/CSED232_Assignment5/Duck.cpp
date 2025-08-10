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

void Duck::Skill(BirdList* birdlist) // ����
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
	
	this->did_kill = 1;

}

