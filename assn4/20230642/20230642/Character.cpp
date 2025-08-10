#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "Character.h"
	
void Character::random_room() { // when you enter the 'random' room
	srand(time(NULL));
	int rand_num = rand() % 4 + 1;
	switch (rand_num) {
	case 1: curr_hp -= floor(curr_hp * 0.3 + 0.5); std::cout << "You lost HP...\n"; break; // losing hp
	case 2: curr_hp * 1.3 < max_hp ? curr_hp += round(curr_hp * 0.3) : curr_hp = max_hp; std::cout << "You restored HP\n"; break; // restore hp
	case 3: gold += 100; std::cout << "You found 100 gold!\n"; break; // find gold
	case 4: std::cout << "Nothing happened...\n"; break; 
	}
	return;
}

void Character::show_status() { // show status of character
	using namespace std;
	cout << "\nLevel: " << level;
	cout << "\nAttack: " << attack;
	cout << "\nDefense: " << defense;
	cout << "\nGold: " << gold;
	cout << "\nHP: " << curr_hp << " / " << max_hp;
	cout << "\nMP: " << curr_mp << " / " << max_mp;
	cout << "\nEXP: " << curr_exp << " / " << max_exp << "\n";
	return;
}

void Character::check_level(int exp) { // check whether curr_exp + reward_exp is enough to level up
	if (exp > max_exp) { // level up
		if (exp - max_exp > (level + 1) * 100) { // if curr_exp is enough to level up twice
			two_level_up(exp);
			return;
		}
		print_level_up(exp); // print level_up status
		level += 1; // update informations
		curr_exp = exp - max_exp;
		max_exp = level * 100;
		attack += 3;
		defense += 1;
		max_hp += 50;
		max_mp += 10;
		curr_hp = max_hp;
		curr_mp = max_mp;
	}
	else { // no level up
		print_state(exp);
		curr_exp = exp;
	}
}


void Character::two_level_up(int exp) { // level up twice
	using namespace std;
	cout << "Level Up!" << endl;
	cout << "=====================================================" << endl;
	cout << "Character status";
	cout << "\nLevel: " << level << " => " << level + 2;
	cout << "\nAttack: " << attack << " => " << attack + 6;
	cout << "\nDefense: " << defense << " => " << defense + 2;
	cout << "\nHP: " << curr_hp << " / " << max_hp << " => " << max_hp + 100 << " / " << max_hp + 5100;
	cout << "\nMP: " << curr_mp << " / " << max_mp << " => " << max_mp + 20 << " / " << max_mp + 20;
	cout << "\nEXP: " << exp << " / " << max_exp << " => " << exp - 100 * (level + 3) << " / " << 100 * (level + 2) << endl;
	cout << "=====================================================" << endl;
	level += 2;
	curr_exp = exp - 100 * level;
	max_exp = level * 100;
	attack += 6;
	defense += 2;
	max_hp += 100;
	max_mp += 20;
	curr_hp = max_hp;
	curr_mp = max_mp;
}

void Character::print_state(int exp) { // print no-level up status
	using namespace std;
	cout << "=====================================================" << endl;
	cout << "Character status";
	cout << "\nLevel: " << level;
	cout << "\nAttack: " << attack;
	cout << "\nDefense: " << defense;
	cout << "\nHP: " << curr_hp << " / " << max_hp;
	cout << "\nMP: " << curr_mp << " / " << max_mp;
	cout << "\nEXP: " << curr_exp << " / " << max_exp << " => " << exp << " / " << max_exp << endl;
	cout << "=====================================================" << endl;
}

void Character::print_level_up(int exp) {
	using namespace std;
	cout << "Level Up!" << endl;
	cout << "=====================================================" << endl;
	cout << "Character status";
	cout << "\nLevel: " << level << " => " << level+1;
	cout << "\nAttack: " << attack << " => " << attack + 3;
	cout << "\nDefense: " << defense << " => " << defense + 1;
	cout << "\nHP: " << curr_hp << " / " << max_hp << " => " << max_hp + 50 << " / " << max_hp + 50;
	cout << "\nMP: " << curr_mp << " / " << max_mp << " => " << max_mp + 10 << " / " << max_mp + 10;
	cout << "\nEXP: " << exp << " / " << max_exp << " => " << exp - max_exp << " / " << 100 * (level + 1) << endl;
	cout << "=====================================================" << endl;
}

void Character::enter_shop() { // print the message when you enter the shop
	std::cout << "\nWelcome to the item shop!" << std::endl;
	std::cout << "You have " << gold << " gold.\n";
}

void Character::buy_attack() { // print informations when you buy attack item
	using namespace std;
	cout << "=====================================================" << endl;
	cout << "Character status";
	cout << "\nLevel: " << level;
	cout << "\nAttack: " << attack << " => " << attack + 10;
	cout << "\nDefense: " << defense;
	cout << "\nHP: " << curr_hp << " / " << max_hp;
	cout << "\nMP: " << curr_mp << " / " << max_mp;
	cout << "\nEXP: " << curr_exp << " / " << max_exp;
	cout << "\n=====================================================" << endl;
}

void Character::buy_defense() { // print informations when you buy defense item
	using namespace std;
	cout << "=====================================================" << endl;
	cout << "Character status";
	cout << "\nLevel: " << level;
	cout << "\nAttack: " << attack;
	cout << "\nDefense: " << defense << " => " << defense + 5;
	cout << "\nHP: " << curr_hp << " / " << max_hp;
	cout << "\nMP: " << curr_mp << " / " << max_mp;
	cout << "\nEXP: " << curr_exp << " / " << max_exp;
	cout << "\n=====================================================" << endl;
}

void Character::restore_hp() { // print messages when you buy restoring hp item
	using namespace std;
	cout << "=====================================================" << endl;
	cout << "Character status";
	cout << "\nLevel: " << level;
	cout << "\nAttack: " << attack;
	cout << "\nDefense: " << defense;
	cout << "\nHP: " << curr_hp << " / " << max_hp << " => " << max_hp << " / " << max_hp;
	cout << "\nMP: " << curr_mp << " / " << max_mp;
	cout << "\nEXP: " << curr_exp << " / " << max_exp;
	cout << "\n=====================================================" << endl;
	curr_hp = max_hp;
}

void Character::restore_mp() { // print messages when you buy restoring mp item
	using namespace std;
	cout << "=====================================================" << endl;
	cout << "Character status";
	cout << "\nLevel: " << level;
	cout << "\nAttack: " << attack;
	cout << "\nDefense: " << defense;
	cout << "\nHP: " << curr_hp << " / " << max_hp;
	cout << "\nMP: " << curr_mp << " / " << max_mp << " => " << max_mp << " / " << max_mp;
	cout << "\nEXP: " << curr_exp << " / " << max_exp;
	cout << "\n=====================================================" << endl;
	curr_mp = max_mp;
}