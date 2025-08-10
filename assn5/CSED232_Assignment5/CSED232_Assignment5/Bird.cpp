#include "Bird.h"
#include <iostream>

Bird::Bird(std::string player_name) {
	this->player_name = player_name;
	alive = 1; // ���� ����ִ� ���¸� 1, ������ 0
	vote = 0; // ���� ���� ��ǥ ��
	did_kill = 0; // �ٸ� ���� �׿����� ����(�׿����� 1, �����)
	number = 7; // ���� ��ȣ
}

Bird::~Bird() {
	this->player_name = "";
}


std::string Bird::GetPlayerName() const {
	return this->player_name;
}

void Bird::SetAlive(bool status) {
	alive = status;
}

bool Bird::IsAlive() const {
	return alive;
}

int Bird::GetNumber() const {
	return number;
}

void Bird::setVote(int num) {
	vote++;
	if (num == 0)
		vote = 0;
}

int Bird::Num_vote() const {
	return vote;
}

void Bird::SetKill(bool status) {
	did_kill = status;
}

bool Bird::Num_kill() const {
	return did_kill;
}

