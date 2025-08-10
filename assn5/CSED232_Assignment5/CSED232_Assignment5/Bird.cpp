#include "Bird.h"
#include <iostream>

Bird::Bird(std::string player_name) {
	this->player_name = player_name;
	alive = 1; // 새가 살아있는 상태면 1, 죽으면 0
	vote = 0; // 새가 받은 투표 수
	did_kill = 0; // 다른 새를 죽였는지 여부(죽였으면 1, 조사용)
	number = 7; // 역할 번호
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

