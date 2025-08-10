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

void DetectiveGoose::Skill(BirdList* birdlist) // ����
{
	std::string who_to_survey;
	std::cout << "�����ϰ� ���� �÷��̾��� �̸��� �Է��ϼ���: ";
	std::cin >> who_to_survey;

	BirdNode* current = birdlist->GetHead();
	while (current->GetBird()->GetPlayerName() != who_to_survey)
		current = current->GetNext();

	if (current->GetBird()->Num_kill() == 1)
		std::cout << who_to_survey << "��(��) �̹� ���忡 �������� ������ �����Ͽ����ϴ�..!\n";

	else
		std::cout << who_to_survey << "��(��) �̹� ���忡 �ƹ��� ��ġ�� �ʾҽ��ϴ�.\n";
}

