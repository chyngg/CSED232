#pragma once
#include <string>

class BirdList;

class Bird
{
protected:
	std::string player_name;
	bool alive; // 살아있으면 1, 죽으면 0
	int vote; // 한 마리의 새가 받은 투표 수
	int number;  // 역할 번호
	int did_kill; // 살조, 암살 등으로 다른 새를 죽였으면 1, 안 죽였으면 0 (조사용)

public:
	Bird(std::string player_name);
	virtual ~Bird();
	std::string GetPlayerName() const;

	void SetAlive(bool status); // 생존 여부 조정
	bool IsAlive() const; // 생존 여부 리턴
	int GetNumber() const; // 역할 번호 리턴
	void setVote(int num); // 득표 수 조정
	int Num_vote() const; // 득표 수 리턴
	void SetKill(bool status); // 살조/암살 여부 조정
	bool Num_kill() const; // 살조/암살 여부 리턴
	virtual void Skill(BirdList* birdlist) = 0; // 순수 추상 함수
	virtual void Skill_2(BirdList* birdlist) {}; // 암살자 오리 - 암살 스킬 사용을 위해 정의
};


