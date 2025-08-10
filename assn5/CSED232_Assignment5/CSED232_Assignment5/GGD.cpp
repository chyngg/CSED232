#include <iostream>
#include <string>
#include "GGD.h"

GGD::GGD() {
	bird_list = new BirdList();
	number_to_kill = 1; // ����� ���� ���� ���� Ƚ��(����Ʈ)
	round = 1; // ���� ���� ����
	num = 0; // ��ü ����ִ� �� ������
	duck_num = 0; // ����ִ� ���� ��
	goose_num = 0; // ����ִ� ���� ��
	dodo_num = 0; // ����ִ� ������ ��
	falcon_num = 0; // ����ִ� �۰�� ��
	win = 7; // �¸� ���� �޼� X -> 0, �¸� ���� �޼� �� �¸��� ���� ��ȣ �ű�
	invalid_vote = 0; // ��ȿǥ ��
	dodo_win = 0; // �������� �¸� ������ �޼��� ��� 1, �޼����� ���� ��� 0
	num_kill_bird = number_to_kill; // ���� ���� ���� Ƚ��
}
GGD::~GGD() {
	round = 0;
	delete bird_list;
}
void GGD::GameStart() {
	int select;
	bool game_start = false;
	while (!game_start) {
		std::cout << "------------���� ���� �޴�-------------\n";
		std::cout << "1. �÷��̾� �߰�\n";
		std::cout << "2. ����� ���� ���� ���� ���� Ƚ�� ����\n";
		std::cout << "3. ���� �����ϱ�!\n";
		std::cout << "---------------------------------------\n";
		std::cout << "�޴� ��ȣ�� �Է��ϼ���: ";
		std::cin >> select;

		switch (select)
		{
		case 1: // �÷��̾� �߰�
			AddPlayer();
			break;
		case 2: // ����� ���� ���� ���� Ƚ�� ����
			std::cout << "���� �Է��ϼ���: ";
			std::cin >> number_to_kill;
			break;
		case 3: // ���� �����ϱ�
			if (IsGameOver() == false && num != 0) // ���� ���� ���� �޼� ���� �˻�
				game_start = true;
			else
				std::cout << "������ ������ �� �����ϴ�!!\n";

			break;
		default:
			break;
		}
	}
	std::cout << "���� ����!!\n";
}
void GGD::RoundProgress() {
	std::cout << "----------------Round " << round << "----------------\n";
	num_kill_bird = number_to_kill; // ���� �� ���� ���� Ƚ�� ����
	Skill_Phase(); // ��ų ���
	Vote_Phase(); // ��ǥ
	Update_num(bird_list); // ��Ƴ��� ���� �� ������Ʈ
	round++;
}

bool GGD::IsGameOver() { // �¸� ���� �޼� ����
	bool res = false;
	
	if (dodo_win == 1) // ������ �¸�
		this->win = 6;
	else if (falcon_num == 1 && num - falcon_num <= 1) // �۰�� �¸�
		this->win = 0;
	else if (goose_num > 0 && falcon_num == 0 && duck_num == 0) // ���� �¸�
		this->win = 5;
	else if (duck_num > 0 && (duck_num >= num - duck_num && !(duck_num == 1 && falcon_num == 1))) // ���� �¸�
		this->win = 2;
	

	if (this->win != 7) // ������ �¸��� ���
		res = true;

	return res;
}

void GGD::PrintGameResult() {
	std::cout << "��ü �޽���: " << BirdRoleName[this->win] << "�� �¸��Դϴ�!\n";
	return;
}

void GGD::AddPlayer() { // �÷��̾� �߰�
	std::string player_name;
	std::cout << "�÷��̾��� �̸��� �Է����ּ���: ";
	std::cin >> player_name;

	int role_code;
	std::cout << "���� ��ȣ�� �Է����ּ���: ";
	std::cin >> role_code;

	Bird* new_bird = nullptr;
	switch (BirdRoleCode(role_code)) {
	case BirdRoleCode::kFalcon: // �۰�� �߰�
		new_bird = new Falcon(player_name);
		falcon_num++;
		break;
	case BirdRoleCode::kAssassinDuck: // �ϻ��� ���� �߰�
		new_bird = new AssassinDuck(player_name);
		duck_num++;
		break;
	case BirdRoleCode::kDuck: // ���� �߰�
		new_bird = new Duck(player_name);
		duck_num++;
		break;
	case BirdRoleCode::kDetectiveGoose: // Ž�� ���� �߰�
		new_bird = new DetectiveGoose(player_name);
		goose_num++;
		break;
	case BirdRoleCode::kMorticianGoose: // ���ǻ� ���� �߰�
		new_bird = new MorticianGoose(player_name);
		goose_num++;
		break;
	case BirdRoleCode::kGoose: // ���� �߰�
		new_bird = new Goose(player_name);
		goose_num++;
		break;
	case BirdRoleCode::kDodoBird: // ������ �߰�
		new_bird = new DodoBird(player_name);
		dodo_num++;
		break;
	default:
		break;

	}

	if (new_bird != nullptr) {
		BirdNode* node = new BirdNode(new_bird); // Bird ��� ����
		num++;
		bird_list->AddBirdNode(node);  // BirdList�� ��� �߰�
	}
	else {
		std::cout << "�߸��� ���� ��ȣ�Դϴ�.\n";
	}

}

void GGD::Skill_Phase() // ��ų ��� ������
{
	int num_kill_bird = number_to_kill;
	char skill = ' ';
	BirdNode* temp = bird_list->GetHead();
	while (temp != nullptr) { // �۰�� ��ų ��� (����)
		if (temp->GetBird()->GetNumber() == 0 && temp->GetBird()->IsAlive() == true) { // ����ִ� �۰�ſ� ���Ͽ� ��ų ���
			std::cout << temp->GetBird()->GetPlayerName() << "�� ����� �۰���Դϴ�.\n";
			std::cout << "������ ����Ͻðڽ��ϱ�? [Y/N]: ";
			std::cin >> skill;

			if (skill == 'Y' || skill == 'y') {
				temp->GetBird()->Skill(bird_list);
			}
				
		}
		temp = temp->GetNext(); // Birdlist�� ������ ���ʴ�� �˻�
	}

	temp = bird_list->GetHead();
	while (temp != nullptr) { // �ϻ��� ���� ��ų ���(�ϻ�, ����)
		if (temp->GetBird()->GetNumber() == 1 && temp->GetBird()->IsAlive() == true) { // ����ִ� �ϻ��� ������ ���Ͽ� ��ų ���
			std::cout << temp->GetBird()->GetPlayerName() << "�� ����� �ϻ��� �����Դϴ�.\n";
			std::cout << "�ϻ��� ����Ͻðڽ��ϱ�? [Y/N]: ";
			std::cin >> skill;

			if (skill == 'Y' || skill == 'y')
				temp->GetBird()->Skill(bird_list);

			if (temp->GetBird()->IsAlive() == true) { // �ϻ� ��� �� ���� �ʾ��� ��
				std::cout << "������ ����Ͻðڽ��ϱ�? [Y/N]: ";
				std::cin >> skill;

				if ((skill == 'Y' || skill == 'y') && num_kill_bird > 0) {
					temp->GetBird()->Skill_2(bird_list); // ����
					num_kill_bird--; // ���� ���� Ƚ�� ����
				} 
				else if ((skill == 'Y' || skill == 'y') && num_kill_bird == 0) // ���� �� ���� ���� Ƚ�� ����
					std::cout << "����� ���� ������ ���� ���� Ƚ���� �����Ͽ����ϴ�.\n";
			
			}
		}
		temp = temp->GetNext(); // Birdlist�� ������ ���ʴ�� �˻�
	}

	temp = bird_list->GetHead();
	while (temp != nullptr) { // ���� ��ų ���(����)
		if (temp->GetBird()->GetNumber() == 2 && temp->GetBird()->IsAlive() == true) {
			std::cout << temp->GetBird()->GetPlayerName() << "�� ����� �����Դϴ�.\n";
			std::cout << "������ ����Ͻðڽ��ϱ�? [Y/N]: ";
			std::cin >> skill;
			if ((skill == 'Y' || skill == 'y') && num_kill_bird > 0) {
				temp->GetBird()->Skill(bird_list);
				num_kill_bird--; // ���� ���� Ƚ�� ����
			}
			else if ((skill == 'Y' || skill == 'y') && num_kill_bird == 0) { // ���� �� ���� ���� Ƚ�� ����
				std::cout << "����� ���� ������ ���� ���� Ƚ���� �����Ͽ����ϴ�.\n";
			}
		}
		temp = temp->GetNext(); // Birdlist�� ������ ���ʴ�� �˻�
	}

	temp = bird_list->GetHead();
	while (temp != nullptr) {
		if (temp->GetBird()->GetNumber() == 3 && temp->GetBird()->IsAlive() == true) { // Ž�� ���� ��ų ���(����)
			std::cout << temp->GetBird()->GetPlayerName() << "�� ����� Ž�� �����Դϴ�.\n";
			std::cout << "���縦 ����Ͻðڽ��ϱ�? [Y/N]: ";
			std::cin >> skill;
			if (skill == 'y' || skill == 'Y')
				temp->GetBird()->Skill(bird_list);
		}
		temp = temp->GetNext(); // Birdlist�� ������ ���ʴ�� �˻�
	}

	temp = bird_list->GetHead();
	while (temp != nullptr) {
		if (temp->GetBird()->GetNumber() == 4 && temp->GetBird()->IsAlive() == true) { // ���ǻ� ���� ��ų ���(����)
			std::cout << temp->GetBird()->GetPlayerName() << "�� ����� ���ǻ� �����Դϴ�.\n";
			std::cout << "������ ����Ͻðڽ��ϱ�? [Y/N]: ";
			std::cin >> skill;
			if (skill == 'y' || skill == 'Y')
				temp->GetBird()->Skill(bird_list);
		}
		temp = temp->GetNext(); // Birdlist�� ������ ���ʴ�� �˻�
	}

	temp = bird_list->GetHead();
	while (temp != nullptr) {
		if (temp->GetBird()->GetNumber() == 5 && temp->GetBird()->IsAlive() == true) { // ���� - �ɷ�X
			std::cout << temp->GetBird()->GetPlayerName() << "�� ����� �����Դϴ�.\n";
			temp->GetBird()->Skill(bird_list);
		}
		temp = temp->GetNext();
	}

	temp = bird_list->GetHead();
	while (temp != nullptr) {
		if (temp->GetBird()->GetNumber() == 6 && temp->GetBird()->IsAlive() == true) { // ������ - �ɷ�X
			std::cout << temp->GetBird()->GetPlayerName() << "�� ����� �������Դϴ�.\n";
			temp->GetBird()->Skill(bird_list);
		}
		temp = temp->GetNext();
	}
}

void GGD::Vote_Phase() // ��ǥ ������
{
	BirdNode* temp = bird_list->GetHead(); // bird list�� ������ ���ʴ�� �˻�
	char vote_ = ' '; // ��ǥ�� �������� ����(Y/N)
	std::string who_to_vote = "";
	while (temp != nullptr) {
		if (temp->GetBird()->IsAlive() == true) { // ����ִ� ������ ���Ͽ� �˻�
			if (temp->GetBird()->GetNumber() == 0) { // �۰�� - �ڵ� ��ȿǥ
				std::cout << temp->GetBird()->GetPlayerName() << "���� �۰���̹Ƿ� ��ȿǥ�� �ڵ� ��ǥ�˴ϴ�.\n";
				invalid_vote++; // ��ȿǥ
			}

			else { // �۰�� �̿��� ����
				std::cout << temp->GetBird()->GetPlayerName() << "�� ��ǥ�� �Ͻðڽ��ϱ�? [Y/N]: ";
				std::cin >> vote_;

				if (vote_ == 'y' || vote_ == 'Y') {
					std::cout << "��ǥ�ϰ� ���� �÷��̾��� �̸��� �Է��ϼ���: ";
					std::cin >> who_to_vote;

					BirdNode* temp_2 = bird_list->GetHead();
					while (temp_2 != nullptr) {
						if (temp_2->GetBird()->GetPlayerName() == who_to_vote && temp_2->GetBird()->IsAlive()) {
							temp_2->GetBird()->setVote(1); // ��ǥ �� 1��ŭ ����
							break;
						}
						temp_2 = temp_2->GetNext();
					}
				}
				else { // N ���� ��
					invalid_vote++; // ��ȿǥ
				}
			}
		}
		temp = temp->GetNext();
	}

	temp = bird_list->GetHead();
	int max = temp->GetBird()->Num_vote(); // �ִ� ��ǥ��
	BirdNode* maximum = temp; // �ִ� ��ǥ��
	int duplicated = 0; // �ִ� ��ǥ�ڰ� �ߺ��� ��� 1, �ƴ� ��� 0

	temp = temp->GetNext();
	while (temp != nullptr) {
		if (temp->GetBird()->Num_vote() > max) {
			duplicated = 0; // �ߺ��� �ƴ� ���
			max = temp->GetBird()->Num_vote();
			maximum = temp; 
		}
		else if (temp->GetBird()->Num_vote() == max) // �ִ� ��ǥ�� �ߺ��� ���
			duplicated = 1;

		temp = temp->GetNext();
	}

	if (duplicated == 1 || invalid_vote >= max) { // ��ȿǥ�� �ִ� ��ǥ���� ���ų�, �ִ� ��ǥ�ڰ� �ߺ��� ���
		std::cout << "��ü �޽���: �̹� ��ǥ������ �ƹ� ������ ��÷���� �ʾҽ��ϴ�.\n";
	}
	else {
		maximum->GetBird()->SetAlive(false); // �߹�
		std::cout << "��ü �޽���: " << maximum->GetBird()->GetPlayerName() << "��(��) �� ���� ������ �����ϴ�.\n";

		if (maximum->GetBird()->GetNumber() == 1 || maximum->GetBird()->GetNumber() == 2) { // �߹���� ���� ������ ���
			std::cout << "��ü �޽���: ���� " << maximum->GetBird()->GetPlayerName() << "��(��) �����Դϴ�!!\n";
		}
		else { // �߹���� ���� ������ �ƴ� ���
			std::cout << "��ü �޽���: ���һ� " << maximum->GetBird()->GetPlayerName() << "��(��) ������ �ƴմϴ�!!\n";
		}

		if (maximum->GetBird()->GetNumber() == 6) // �������� �߹���� ��� -> ������ �¸�
			dodo_win = 1;
	}

	BirdNode* temp3 = bird_list->GetHead();
	while (temp3 != nullptr) // ���� ���� �� ��� ���� ��ǥ ��, ���� ������ �ʱ�ȭ
	{
		temp3->GetBird()->setVote(0);
		temp3->GetBird()->SetKill(0);
		temp3 = temp3->GetNext();
	}

}

void GGD::Update_num(BirdList* birdlist) // ��ų ���, ��ǥ ���� �� ����ִ� ���� �� ������Ʈ
{
	falcon_num = 0;
	duck_num = 0;
	goose_num = 0;
	dodo_num = 0;
	num = 0;

	BirdNode* temp = birdlist->GetHead();

	while (temp != nullptr)
	{
		if (temp->GetBird()->IsAlive()) // ����ִ� �� ī��Ʈ
		{
			switch (temp->GetBird()->GetNumber())
			{
			case 0: falcon_num++; break; // �۰��
			case 1: duck_num++; break; // (�ϻ���) ����
			case 2: duck_num++; break; // ����
			case 3: goose_num++; break; // (Ž��) ����
			case 4: goose_num++; break; // (���ǻ�) ����
			case 5: goose_num++; break; // ����
			case 6: dodo_num++; break; // ������
			default: break;
			}
			num++; // ��ü �� ��
		}
		temp = temp->GetNext();
	}
}

