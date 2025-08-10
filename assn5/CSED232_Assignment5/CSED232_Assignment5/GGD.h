#pragma once
#include "Bird.h"
#include "BirdNode.h"
#include "Duck.h"
#include "Falcon.h"
#include "AssassinDuck.h"
#include "DodoBird.h"
#include "Goose.h"
#include "DetectiveGoose.h"
#include "MorticianGoose.h"
#include "BirdList.h"
#include "Macro.h"
#include "BirdList.h"

class GGD
{
private:
	BirdList* bird_list;
	int number_to_kill;
	int round;
	int num;
	int duck_num;
	int goose_num;
	int dodo_num;
	int falcon_num;
	int win;
	int invalid_vote;
	bool dodo_win;
	int num_kill_bird; 

public:
	// Do not change any function declaration from here //
	GGD();
	~GGD();
	void GameStart();
	void RoundProgress();
	bool IsGameOver();
	void PrintGameResult();
	// Do not change any function declaration to here //

	void AddPlayer(); // You can change the function declaration

	void Skill_Phase();
	void Vote_Phase();
	void Update_num(BirdList* birdlist); // 살아남은 조류 수 업데이트

};

