#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "Monster.h"
#include "Character.h"

Monster::Monster(int difficulty) // Constructor -> initialize member values
{
	srand(time(NULL));
	init_hp = 50 + difficulty * 5; 
	curr_hp = init_hp;
	attack = 5 + difficulty * 2;
	defense = 2 + round(difficulty / 2);
	reward_gold = 100 + difficulty * 10;
	reward_exp = 100 + difficulty * 10;
	int rand_num = rand() % 4 + 1;
	switch (rand_num) { // determine type of monster
	case 1: type = fire; break;
	case 2: type = grass; break;
	case 3: type = water; break;
	case 4: type = nothing; break;
	default: type = nothing; break;
	}
}

Monster::~Monster() {}

int Monster::fight(Character &ch) { // when you meet monster -> fight
	using namespace std;
	int action;

	while (ch.curr_hp >= 0 && curr_hp >= 0) {
		cout << "=====================================================" << endl;
		cout << "Character status";
		ch.show_status(); // print character's status
		cout << "=====================================================" << endl;
		show_monster_state(); // print monster's status
		cout << "=====================================================" << endl;


		cout << "Choose your action" << endl; 
		cout << "1. Meele attack" << endl;
		cout << "2. Magic attack" << endl;
		cout << "3. Fire magic attack" << endl;
		cout << "4. Grass magic attack" << endl;
		cout << "5. Water magic attack\n> ";
		cin >> action;

		if (action == 1)
			attack_basic(ch); // meele attack
		else if (action == 2)
			attack_skill(ch); // magic attack
		else if (action == 3)
			attack_fire(ch); // fire magic attack
		else if (action == 4)
			attack_grass(ch); // grass magic attack
		else
			attack_water(ch); // water magic attack
		
		attack_by_monster(ch); // character is attacked by monster
		if (ch.curr_hp < 0) { // if character's hp < 0
			cout << "\nYou died..." << endl; // character die
			return 0; // end program
		}

		if (curr_hp < 0) { // when monster's hp < 0 -> you defeat the monster
			cout << "You defeated the monster!" << endl; 
			cout << "Reward: " << reward_gold << " Gold, " << reward_exp << " EXP\n" << endl;

			ch.gold += reward_gold; // get reward_gold
			ch.check_level(reward_exp + ch.curr_exp); // check whether exp is enough to level up
			return 1; // defeat monster
		}
	}
}

void Monster::attack_basic(Character &ch) { // meele attack
	int attack_monster = ch.attack > defense ? ch.attack - defense : 0;
	curr_hp -= attack_monster;
	std::cout << "You hit the monster with " << attack_monster  << " damage!\n";
}

void Monster::attack_skill(Character &ch) { // magic attack
	if (ch.curr_mp < 15) { // when mp is not enough 
		std::cout << "\nNot enough MP...\n";
		return;
	}
	int attack_monster = floor(ch.attack * 1.5 + 0.5) > defense ? floor(ch.attack * 1.5 + 0.5) - defense : 0;
	curr_hp -= attack_monster; // monster is attacked by character
	ch.curr_mp -= 15; // character's mp decreases
	std::cout << "You hit the monster with " << attack_monster << " damage!\n";
}

void Monster::attack_fire(Character &ch) { // fire magic attack
	if (ch.curr_mp < 15) {
		std::cout << "\nNot enough MP...\n"; 
		return;
	}
	int attack_monster = 0;
	if (type == grass) { // when monster's type is grass
		attack_monster = (ch.attack * 2 > defense) ? ch.attack * 2 - defense : 0;
		curr_hp -= attack_monster;
		std::cout << "You hit the monster with " << attack_monster << " damage!\n";
	}
	else {
		attack_monster = (ch.attack > defense) ? ch.attack - defense : 0;
		curr_hp -= attack_monster;
		std::cout << "You hit the monster with " << attack_monster << " damage!\n";
	}
	ch.curr_mp -= 15;
}

void Monster::attack_grass(Character &ch) { // grass magic attack
	if (ch.curr_mp < 15) {
		std::cout << "\nNot enough MP...\n";
		return;
	}
	int attack_monster;
	if (type == water) { // when monster's type is water
		attack_monster = (ch.attack * 2 > defense) ? ch.attack * 2 - defense : 0;
		curr_hp -= attack_monster;
		std::cout << "You hit the monster with " << attack_monster << " damage!\n";
	}
	else { 
		attack_monster = (ch.attack > defense) ? ch.attack - defense : 0;
		curr_hp -= attack_monster;
		std::cout << "You hit the monster with " << attack_monster << " damage!\n";
	}
	ch.curr_mp -= 15;
}

void Monster::attack_water(Character &ch) { // water magic attack
	if (ch.curr_mp < 15) {
		std::cout << "\nNot enough MP...\n";
		return;
	}
	int attack_monster;
	if (type == fire) { // when monster's type is fire
		attack_monster = (ch.attack * 2 > defense) ? ch.attack * 2 - defense : 0;
		curr_hp -= attack_monster;
		std::cout << "You hit the monster with " << attack_monster << " damage!\n";
	}
	else {
		attack_monster = (ch.attack > defense) ? ch.attack - defense : 0;
		curr_hp -= attack_monster;
		std::cout << "You hit the monster with " << attack_monster << " damage!\n";
	}
	ch.curr_mp -= 15;
}

void Monster::attack_by_monster(Character &ch) { // character is attacked by monster
	int attack_character = attack > ch.defense ? attack - ch.defense : 0;
	ch.curr_hp -= attack_character;
	std::cout << "Monster hit you with " << attack_character << " damage!\n\n";
}

void Monster::show_monster_state() {
	std::cout << "Monster status\n";
	std::cout << "Attack: " << attack << std::endl;
	std::cout << "Defense: " << defense << std::endl;
	std::cout << "HP: " << curr_hp << " / " << init_hp << std::endl;
}

void Monster::boss() { // when you meet boss monster -> initialized monster's values are changed
	srand(time(NULL));
	init_hp = 200;
	curr_hp = init_hp;
	attack = 30;
	defense = 10;
	int rand_num = rand() % 4 + 1;
	switch (rand_num) {
	case 1: type = fire; break;
	case 2: type = grass; break;
	case 3: type = water; break;
	case 4: type = nothing; break;
	}
}

int Monster::fight_boss(Character &ch) { // when you meet the boss -> fight
	using namespace std;
	int action = 6;

	while (curr_hp >= 0 && ch.curr_hp >= 0) {
		cout << "=====================================================" << endl;
		cout << "Character status" << endl;
		ch.show_status();
		cout << "=====================================================" << endl;
		show_monster_state();
		cout << "=====================================================" << endl;


		cout << "Choose your action" << endl;
		cout << "1. Meele attack" << endl;
		cout << "2. Magic attack" << endl;
		cout << "3. Fire magic attack" << endl;
		cout << "4. Grass magic attack" << endl;
		cout << "5. Water magic attack";
		while (action < 1 || action > 5) {
			cout << "\n> ";
			cin >> action;
		}
		
		if (action == 1)
			attack_basic(ch);
		else if (action == 2)
			attack_skill(ch);
		else if (action == 3)
			attack_fire(ch);
		else if (action == 4)
			attack_grass(ch);
		else
			attack_water(ch);

		attack_by_monster(ch);
		if (ch.curr_hp < 0) {
			cout << "\nYou died..." << endl;
			return 0;
		}

		if (curr_hp < 0) // when you defeat the boss
			return 1; // end program
	}
		
}