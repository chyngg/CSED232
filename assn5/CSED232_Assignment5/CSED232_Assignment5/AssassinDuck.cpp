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

void AssassinDuck::Skill(BirdList* birdlist) // �ϻ�
{
	if (assassin_limit == 0) // �ϻ� ���� Ƚ�� ���� ��
	{
		std::cout << "�� �̻� �ϻ� �ɷ��� ����� �� �����ϴ�!\n";
		return;
	}

	std::string who_to_kill;
	int player_num;
	std::cout << "�ϻ��ϰ� ���� �÷��̾��� �̸��� �Է��ϼ���: ";
	std::cin >> who_to_kill;
	std::cout << "�ϻ��ϰ� ���� �÷��̾��� ���� ��ȣ�� �Է��ϼ���: ";
	std::cin >> player_num;

	BirdNode* current = nullptr;
	current = birdlist->GetHead();
	while (current->GetBird()->GetPlayerName() != who_to_kill)
		current = current->GetNext();

	if (current->GetBird()->GetNumber() == player_num) // �÷��̾��� ���� ��ȣ�� ������ ��
	{
		std::cout << "��ü �޽���: " << who_to_kill << "��(��) ������ ���ش��Ͽ����ϴ�..\n";
		current->GetBird()->SetAlive(false);
		this->assassin_limit--;
		this->did_kill = 1;
	}

	else // ���� ��ȣ�� �� ������ ��
	{
		std::cout << "��ü �޽���: " << player_name << "��(��) �ش��� ������ �Ͽ����ϴ�.\n";
		this->alive = 0;
	}
	
}

void AssassinDuck::Skill_2(BirdList* birdlist) // ����
{
	Duck::Skill(birdlist); // Duck Ŭ������ Skill�� ����� ����(����)
}
