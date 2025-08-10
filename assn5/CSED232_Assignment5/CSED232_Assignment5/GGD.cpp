#include <iostream>
#include <string>
#include "GGD.h"

GGD::GGD() {
	bird_list = new BirdList();
	number_to_kill = 1; // 라운드당 오리 살조 제한 횟수(디폴트)
	round = 1; // 진행 중인 라운드
	num = 0; // 전체 살아있는 새 마리수
	duck_num = 0; // 살아있는 오리 수
	goose_num = 0; // 살아있는 거위 수
	dodo_num = 0; // 살아있는 도도새 수
	falcon_num = 0; // 살아있는 송골매 수
	win = 7; // 승리 조건 달성 X -> 0, 승리 조건 달성 시 승리한 조류 번호 매김
	invalid_vote = 0; // 무효표 수
	dodo_win = 0; // 도도새가 승리 조건을 달성할 경우 1, 달성하지 않을 경우 0
	num_kill_bird = number_to_kill; // 오리 살조 가능 횟수
}
GGD::~GGD() {
	round = 0;
	delete bird_list;
}
void GGD::GameStart() {
	int select;
	bool game_start = false;
	while (!game_start) {
		std::cout << "------------게임 설정 메뉴-------------\n";
		std::cout << "1. 플레이어 추가\n";
		std::cout << "2. 라운드당 오리 진영 살조 제한 횟수 설정\n";
		std::cout << "3. 게임 시작하기!\n";
		std::cout << "---------------------------------------\n";
		std::cout << "메뉴 번호를 입력하세요: ";
		std::cin >> select;

		switch (select)
		{
		case 1: // 플레이어 추가
			AddPlayer();
			break;
		case 2: // 라운드당 오리 살조 제한 횟수 변경
			std::cout << "값을 입력하세요: ";
			std::cin >> number_to_kill;
			break;
		case 3: // 게임 시작하기
			if (IsGameOver() == false && num != 0) // 게임 시작 조건 달성 여부 검사
				game_start = true;
			else
				std::cout << "게임을 시작할 수 없습니다!!\n";

			break;
		default:
			break;
		}
	}
	std::cout << "게임 시작!!\n";
}
void GGD::RoundProgress() {
	std::cout << "----------------Round " << round << "----------------\n";
	num_kill_bird = number_to_kill; // 라운드 당 살조 가능 횟수 설정
	Skill_Phase(); // 스킬 사용
	Vote_Phase(); // 투표
	Update_num(bird_list); // 살아남은 조류 수 업데이트
	round++;
}

bool GGD::IsGameOver() { // 승리 조건 달성 여부
	bool res = false;
	
	if (dodo_win == 1) // 도도새 승리
		this->win = 6;
	else if (falcon_num == 1 && num - falcon_num <= 1) // 송골매 승리
		this->win = 0;
	else if (goose_num > 0 && falcon_num == 0 && duck_num == 0) // 거위 승리
		this->win = 5;
	else if (duck_num > 0 && (duck_num >= num - duck_num && !(duck_num == 1 && falcon_num == 1))) // 오리 승리
		this->win = 2;
	

	if (this->win != 7) // 누군가 승리한 경우
		res = true;

	return res;
}

void GGD::PrintGameResult() {
	std::cout << "전체 메시지: " << BirdRoleName[this->win] << "의 승리입니다!\n";
	return;
}

void GGD::AddPlayer() { // 플레이어 추가
	std::string player_name;
	std::cout << "플레이어의 이름을 입력해주세요: ";
	std::cin >> player_name;

	int role_code;
	std::cout << "역할 번호를 입력해주세요: ";
	std::cin >> role_code;

	Bird* new_bird = nullptr;
	switch (BirdRoleCode(role_code)) {
	case BirdRoleCode::kFalcon: // 송골매 추가
		new_bird = new Falcon(player_name);
		falcon_num++;
		break;
	case BirdRoleCode::kAssassinDuck: // 암살자 오리 추가
		new_bird = new AssassinDuck(player_name);
		duck_num++;
		break;
	case BirdRoleCode::kDuck: // 오리 추가
		new_bird = new Duck(player_name);
		duck_num++;
		break;
	case BirdRoleCode::kDetectiveGoose: // 탐정 거위 추가
		new_bird = new DetectiveGoose(player_name);
		goose_num++;
		break;
	case BirdRoleCode::kMorticianGoose: // 장의사 거위 추가
		new_bird = new MorticianGoose(player_name);
		goose_num++;
		break;
	case BirdRoleCode::kGoose: // 거위 추가
		new_bird = new Goose(player_name);
		goose_num++;
		break;
	case BirdRoleCode::kDodoBird: // 도도새 추가
		new_bird = new DodoBird(player_name);
		dodo_num++;
		break;
	default:
		break;

	}

	if (new_bird != nullptr) {
		BirdNode* node = new BirdNode(new_bird); // Bird 노드 생성
		num++;
		bird_list->AddBirdNode(node);  // BirdList에 노드 추가
	}
	else {
		std::cout << "잘못된 역할 번호입니다.\n";
	}

}

void GGD::Skill_Phase() // 스킬 사용 페이즈
{
	int num_kill_bird = number_to_kill;
	char skill = ' ';
	BirdNode* temp = bird_list->GetHead();
	while (temp != nullptr) { // 송골매 스킬 사용 (살조)
		if (temp->GetBird()->GetNumber() == 0 && temp->GetBird()->IsAlive() == true) { // 살아있는 송골매에 한하여 스킬 사용
			std::cout << temp->GetBird()->GetPlayerName() << "님 당신은 송골매입니다.\n";
			std::cout << "살조를 사용하시겠습니까? [Y/N]: ";
			std::cin >> skill;

			if (skill == 'Y' || skill == 'y') {
				temp->GetBird()->Skill(bird_list);
			}
				
		}
		temp = temp->GetNext(); // Birdlist의 헤드부터 차례대로 검사
	}

	temp = bird_list->GetHead();
	while (temp != nullptr) { // 암살자 오리 스킬 사용(암살, 살조)
		if (temp->GetBird()->GetNumber() == 1 && temp->GetBird()->IsAlive() == true) { // 살아있는 암살자 오리에 한하여 스킬 사용
			std::cout << temp->GetBird()->GetPlayerName() << "님 당신은 암살자 오리입니다.\n";
			std::cout << "암살을 사용하시겠습니까? [Y/N]: ";
			std::cin >> skill;

			if (skill == 'Y' || skill == 'y')
				temp->GetBird()->Skill(bird_list);

			if (temp->GetBird()->IsAlive() == true) { // 암살 사용 후 죽지 않았을 때
				std::cout << "살조를 사용하시겠습니까? [Y/N]: ";
				std::cin >> skill;

				if ((skill == 'Y' || skill == 'y') && num_kill_bird > 0) {
					temp->GetBird()->Skill_2(bird_list); // 살조
					num_kill_bird--; // 살조 가능 횟수 차감
				} 
				else if ((skill == 'Y' || skill == 'y') && num_kill_bird == 0) // 라운드 당 살조 제한 횟수 도달
					std::cout << "라운드당 오리 진영의 살조 제한 횟수에 도달하였습니다.\n";
			
			}
		}
		temp = temp->GetNext(); // Birdlist의 헤드부터 차례대로 검사
	}

	temp = bird_list->GetHead();
	while (temp != nullptr) { // 오리 스킬 사용(살조)
		if (temp->GetBird()->GetNumber() == 2 && temp->GetBird()->IsAlive() == true) {
			std::cout << temp->GetBird()->GetPlayerName() << "님 당신은 오리입니다.\n";
			std::cout << "살조를 사용하시겠습니까? [Y/N]: ";
			std::cin >> skill;
			if ((skill == 'Y' || skill == 'y') && num_kill_bird > 0) {
				temp->GetBird()->Skill(bird_list);
				num_kill_bird--; // 살조 가능 횟수 차감
			}
			else if ((skill == 'Y' || skill == 'y') && num_kill_bird == 0) { // 라운드 당 살조 제한 횟수 도달
				std::cout << "라운드당 오리 진영의 살조 제한 횟수에 도달하였습니다.\n";
			}
		}
		temp = temp->GetNext(); // Birdlist의 헤드부터 차례대로 검사
	}

	temp = bird_list->GetHead();
	while (temp != nullptr) {
		if (temp->GetBird()->GetNumber() == 3 && temp->GetBird()->IsAlive() == true) { // 탐정 거위 스킬 사용(조사)
			std::cout << temp->GetBird()->GetPlayerName() << "님 당신은 탐정 거위입니다.\n";
			std::cout << "조사를 사용하시겠습니까? [Y/N]: ";
			std::cin >> skill;
			if (skill == 'y' || skill == 'Y')
				temp->GetBird()->Skill(bird_list);
		}
		temp = temp->GetNext(); // Birdlist의 헤드부터 차례대로 검사
	}

	temp = bird_list->GetHead();
	while (temp != nullptr) {
		if (temp->GetBird()->GetNumber() == 4 && temp->GetBird()->IsAlive() == true) { // 장의사 거위 스킬 사용(염습)
			std::cout << temp->GetBird()->GetPlayerName() << "님 당신은 장의사 거위입니다.\n";
			std::cout << "염습을 사용하시겠습니까? [Y/N]: ";
			std::cin >> skill;
			if (skill == 'y' || skill == 'Y')
				temp->GetBird()->Skill(bird_list);
		}
		temp = temp->GetNext(); // Birdlist의 헤드부터 차례대로 검사
	}

	temp = bird_list->GetHead();
	while (temp != nullptr) {
		if (temp->GetBird()->GetNumber() == 5 && temp->GetBird()->IsAlive() == true) { // 거위 - 능력X
			std::cout << temp->GetBird()->GetPlayerName() << "님 당신은 거위입니다.\n";
			temp->GetBird()->Skill(bird_list);
		}
		temp = temp->GetNext();
	}

	temp = bird_list->GetHead();
	while (temp != nullptr) {
		if (temp->GetBird()->GetNumber() == 6 && temp->GetBird()->IsAlive() == true) { // 도도새 - 능력X
			std::cout << temp->GetBird()->GetPlayerName() << "님 당신은 도도새입니다.\n";
			temp->GetBird()->Skill(bird_list);
		}
		temp = temp->GetNext();
	}
}

void GGD::Vote_Phase() // 투표 페이즈
{
	BirdNode* temp = bird_list->GetHead(); // bird list의 헤드부터 차례대로 검사
	char vote_ = ' '; // 투표에 참여할지 저장(Y/N)
	std::string who_to_vote = "";
	while (temp != nullptr) {
		if (temp->GetBird()->IsAlive() == true) { // 살아있는 조류에 한하여 검사
			if (temp->GetBird()->GetNumber() == 0) { // 송골매 - 자동 무효표
				std::cout << temp->GetBird()->GetPlayerName() << "님은 송골매이므로 무효표에 자동 투표됩니다.\n";
				invalid_vote++; // 무효표
			}

			else { // 송골매 이외의 조류
				std::cout << temp->GetBird()->GetPlayerName() << "님 투표를 하시겠습니까? [Y/N]: ";
				std::cin >> vote_;

				if (vote_ == 'y' || vote_ == 'Y') {
					std::cout << "투표하고 싶은 플레이어의 이름을 입력하세요: ";
					std::cin >> who_to_vote;

					BirdNode* temp_2 = bird_list->GetHead();
					while (temp_2 != nullptr) {
						if (temp_2->GetBird()->GetPlayerName() == who_to_vote && temp_2->GetBird()->IsAlive()) {
							temp_2->GetBird()->setVote(1); // 득표 수 1만큼 증가
							break;
						}
						temp_2 = temp_2->GetNext();
					}
				}
				else { // N 응답 시
					invalid_vote++; // 무효표
				}
			}
		}
		temp = temp->GetNext();
	}

	temp = bird_list->GetHead();
	int max = temp->GetBird()->Num_vote(); // 최다 득표수
	BirdNode* maximum = temp; // 최다 득표자
	int duplicated = 0; // 최다 득표자가 중복인 경우 1, 아닌 경우 0

	temp = temp->GetNext();
	while (temp != nullptr) {
		if (temp->GetBird()->Num_vote() > max) {
			duplicated = 0; // 중복이 아닌 경우
			max = temp->GetBird()->Num_vote();
			maximum = temp; 
		}
		else if (temp->GetBird()->Num_vote() == max) // 최다 득표자 중복인 경우
			duplicated = 1;

		temp = temp->GetNext();
	}

	if (duplicated == 1 || invalid_vote >= max) { // 무효표가 최다 득표보다 많거나, 최다 득표자가 중복인 경우
		std::cout << "전체 메시지: 이번 투표에서는 아무 조류도 당첨되지 않았습니다.\n";
	}
	else {
		maximum->GetBird()->SetAlive(false); // 추방
		std::cout << "전체 메시지: " << maximum->GetBird()->GetPlayerName() << "은(는) 더 좋은 곳으로 갔습니다.\n";

		if (maximum->GetBird()->GetNumber() == 1 || maximum->GetBird()->GetNumber() == 2) { // 추방당한 새가 오리인 경우
			std::cout << "전체 메시지: 만세 " << maximum->GetBird()->GetPlayerName() << "은(는) 오리입니다!!\n";
		}
		else { // 추방당한 새가 오리가 아닌 경우
			std::cout << "전체 메시지: 맙소사 " << maximum->GetBird()->GetPlayerName() << "은(는) 오리가 아닙니다!!\n";
		}

		if (maximum->GetBird()->GetNumber() == 6) // 도도새가 추방당한 경우 -> 도도새 승리
			dodo_win = 1;
	}

	BirdNode* temp3 = bird_list->GetHead();
	while (temp3 != nullptr) // 라운드 종료 후 모든 새의 득표 수, 살조 내역을 초기화
	{
		temp3->GetBird()->setVote(0);
		temp3->GetBird()->SetKill(0);
		temp3 = temp3->GetNext();
	}

}

void GGD::Update_num(BirdList* birdlist) // 스킬 사용, 투표 진행 후 살아있는 조류 수 업데이트
{
	falcon_num = 0;
	duck_num = 0;
	goose_num = 0;
	dodo_num = 0;
	num = 0;

	BirdNode* temp = birdlist->GetHead();

	while (temp != nullptr)
	{
		if (temp->GetBird()->IsAlive()) // 살아있는 새 카운트
		{
			switch (temp->GetBird()->GetNumber())
			{
			case 0: falcon_num++; break; // 송골매
			case 1: duck_num++; break; // (암살자) 오리
			case 2: duck_num++; break; // 오리
			case 3: goose_num++; break; // (탐정) 거위
			case 4: goose_num++; break; // (장의사) 거위
			case 5: goose_num++; break; // 거위
			case 6: dodo_num++; break; // 도도새
			default: break;
			}
			num++; // 전체 새 수
		}
		temp = temp->GetNext();
	}
}

