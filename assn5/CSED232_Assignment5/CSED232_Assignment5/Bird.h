#pragma once
#include <string>

class BirdList;

class Bird
{
protected:
	std::string player_name;
	bool alive; // ��������� 1, ������ 0
	int vote; // �� ������ ���� ���� ��ǥ ��
	int number;  // ���� ��ȣ
	int did_kill; // ����, �ϻ� ������ �ٸ� ���� �׿����� 1, �� �׿����� 0 (�����)

public:
	Bird(std::string player_name);
	virtual ~Bird();
	std::string GetPlayerName() const;

	void SetAlive(bool status); // ���� ���� ����
	bool IsAlive() const; // ���� ���� ����
	int GetNumber() const; // ���� ��ȣ ����
	void setVote(int num); // ��ǥ �� ����
	int Num_vote() const; // ��ǥ �� ����
	void SetKill(bool status); // ����/�ϻ� ���� ����
	bool Num_kill() const; // ����/�ϻ� ���� ����
	virtual void Skill(BirdList* birdlist) = 0; // ���� �߻� �Լ�
	virtual void Skill_2(BirdList* birdlist) {}; // �ϻ��� ���� - �ϻ� ��ų ����� ���� ����
};


