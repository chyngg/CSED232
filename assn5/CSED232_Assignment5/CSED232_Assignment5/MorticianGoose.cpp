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

void MorticianGoose::Skill(BirdList* birdlist) // ����
{
	BirdNode* current = birdlist->GetHead();
	while (current->GetBird()->IsAlive() == 1) {
		current = current->GetNext();
		if (current == nullptr) {
			std::cout << "���� ���� ����� �����ϴ�.\n";
			return;
		}
	}

	std::string who_to_search;
	std::cout << "�����ϰ� ���� �÷��̾��� �̸��� �Է��ϼ��� : ";
	std::cin >> who_to_search;


	current = birdlist->GetHead();
	while (current->GetBird()->GetPlayerName() != who_to_search) {
		current = current->GetNext();
	}
	std::cout << who_to_search << "�� ������ " << BirdRoleName[current->GetBird()->GetNumber()] << "�Դϴ�.\n";
}