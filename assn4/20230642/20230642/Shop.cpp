#include <iostream>
#include "Shop.h"
#include "Character.h"

Shop::Shop() // Constructor: initialize member values
{
	attack_left = 1;
	defense_left = 1;
	exp_left = 1;
}
Shop::~Shop() {}

void Shop::select(Character &ch) { // when you enter the shop
	using namespace std;
	int selection = 0;
	ch.enter_shop(); // print messages (gold) when you enter the shop
	cout << "=====================================================" << endl;
	cout << "=====================Item List=======================" << endl;
	cout << "=====================================================\n" << endl;
	
	if (attack_left >= 1) // when attack_item is available
		cout << "1. Attack +10 (700 Gold) (Available)" << endl;
	else
		cout << "1. Attack +10 (700 Gold) (Sold out)" << endl;


	if (defense_left >= 1) // when defense_item is available
		cout << "2. Defense +5 (700 Gold) (Available)" << endl;
	else
		cout << "2. Defense +5 (700 Gold) (Sold out)" << endl;


	if (exp_left >= 1) // when exp_item is available
		cout << "3. Exp +300 (700 Gold) (Available)" << endl;
	else
		cout << "3. Exp +300 (700 Gold) (Sold out)" << endl;
	
	
	cout << "4. Restore HP (500 Gold) (Always available)" << endl;
	cout << "5. Restore MP (500 Gold) (Always available)" << endl;
	cout << "6. Exit shop\n" << endl;
	cout << "=====================================================" << endl;

	while (selection != 6) { // 6: exit shop
		cout << "> ";
		cin >> selection;

		if (selection == 1) {
			selection = item_attack(ch);
		}
		else if (selection == 2) {
			selection = item_defense(ch);
		}
		else if (selection == 3) {
			selection = item_exp(ch);
		}
		else if (selection == 4) {
			selection = item_hp(ch);
		}
		else if (selection == 5) {
			selection = item_mp(ch);
		}
	}
	return;
	
}

int Shop::item_attack(Character &ch) {
	if (attack_left < 1) { // sold out
		std::cout << "Selected item is not available..." << std::endl;
		return 1;
	}
	else if (ch.gold < 700) { // you don't have enought gold
		std::cout << "You do not have enough gold..." << std::endl;
		return 1;
	}
	// you can buy item
	std::cout << "You bought an item!\n" << std::endl;
	ch.buy_attack();
	ch.attack += 10;
	ch.gold -= 700;
	attack_left -= 1;


	std::cout << "Shop item list\n";
	std::cout << "1. Attack +10 (700 Gold) (Available) => (Sold out)\n";

	if (defense_left >= 1) 
		std::cout << "2. Defense +5 (700 Gold) (Available)" << std::endl;
	else // when defense_item is solded out
		std::cout << "2. Defense +5 (700 Gold) (Sold out)" << std::endl;


	if (exp_left >= 1)
		std::cout << "3. Exp +300 (700 Gold) (Available)" << std::endl;
	else // when exp_item is solded out
		std::cout << "3. Exp +300 (700 Gold) (Sold out)" << std::endl;
	
	std::cout << "4. Restore HP (500 Gold) (Always available)\n";
	std::cout << "5. Restore MP (500 Gold) (Always available)\n";
	std::cout << "=====================================================\n" << std::endl;
	return 6;
}

int Shop::item_defense(Character &ch)
{
	if (defense_left < 1) { // when defense_item is solded out
		std::cout << "Selected item is not available..." << std::endl;
		return 2;
	}
	else if (ch.gold < 700) { // when you don't have enough gold to buy item
		std::cout << "You do not have enough gold..." << std::endl;
		return 2;
	}
	std::cout << "You bought an item!\n" << std::endl;
	
	ch.buy_defense();
	ch.defense += 5;
	ch.gold -= 700;
	defense_left -= 1;

	std::cout << "Shop item list\n"; 

	if (attack_left >= 1) 
		std::cout << "1. Attack +10 (700 Gold) (Available)" << std::endl;
	else // when attack_item is solded out
		std::cout << "1. Attack +10 (700 Gold) (Sold out)" << std::endl;


	std::cout << "2. Defense +5 (700 Gold) (Available) => (Sold out)\n";


	if (exp_left >= 1)
		std::cout << "3. Exp +300 (700 Gold) (Available)" << std::endl;
	else // when attack_item is solded out
		std::cout << "3. Exp +300 (700 Gold) (Sold out)" << std::endl;

	std::cout << "4. Restore HP (500 Gold) (Always available)\n";
	std::cout << "5. Restore MP (500 Gold) (Always available)\n";
	std::cout << "=====================================================\n" << std::endl;
	return 6;
}

int Shop::item_exp(Character &ch) { // when you buy exp_item
	if (exp_left < 1) { // when item is solded out
		std::cout << "Selected item is not available..." << std::endl;
		return 3;
	}
	else if (ch.gold < 700) { // when you don't have enough gold
		std::cout << "You do not have enough gold..." << std::endl;
		return 3;
	}
	// buy item
	std::cout << "You bought an item!\n" << std::endl; 
	ch.check_level(ch.curr_exp + 300); // check whether exp is enough to level up
	ch.gold -= 700;
	exp_left -= 1;

	std::cout << "Shop item list\n";
	if (attack_left >= 1)
		std::cout << "1. Attack +10 (700 Gold) (Available)" << std::endl;
	else // when attack_item is solded 
		std::cout << "1. Attack +10 (700 Gold) (Sold out)" << std::endl;


	if (defense_left >= 1)
		std::cout << "2. Defense +5 (700 Gold) (Available)" << std::endl;
	else // when defense_item is solded
		std::cout << "2. Defense +5 (700 Gold) (Sold out)" << std::endl;

	std::cout << "3. Exp +300 (700 Gold) (Available) => (Sold out)\n";
	std::cout << "4. Restore HP (500 Gold) (Always available)\n";
	std::cout << "5. Restore MP (500 Gold) (Always available)\n";
	std::cout << "=====================================================\n" << std::endl;
	return 6;

}

int Shop::item_hp(Character &ch) {
	if (ch.gold < 500) { // when you don't have enough gold
		std::cout << "You do not have enough gold..." << std::endl;
		return 4;
	}
	std::cout << "You bought an item!\n" << std::endl; 
	ch.restore_hp();

	std::cout << "Shop item list\n";
	if (attack_left >= 1) 
		std::cout << "1. Attack +10 (700 Gold) (Available)" << std::endl;
	else // when attack_item is solded out
		std::cout << "1. Attack +10 (700 Gold) (Sold out)" << std::endl;


	if (defense_left >= 1)
		std::cout << "2. Defense +5 (700 Gold) (Available)" << std::endl;
	else // when defense_item is solded out
		std::cout << "2. Defense +5 (700 Gold) (Sold out)" << std::endl;
	
	
	if (exp_left >= 1)
		std::cout << "3. Exp +300 (700 Gold) (Available)" << std::endl;
	else // when exp_item is solded out
		std::cout << "3. Exp +300 (700 Gold) (Sold out)" << std::endl;


	std::cout << "4. Restore HP (500 Gold) (Always available)\n";
	std::cout << "5. Restore MP (500 Gold) (Always available)\n";
	std::cout << "=====================================================\n" << std::endl;
	return 6;

}

int Shop::item_mp(Character &ch) {
	if (ch.gold < 500) { // when you don't have enough gold to buy
		std::cout << "You do not have enough gold..." << std::endl;
		return 5;
	}
	std::cout << "You bought an item!\n" << std::endl;
	ch.restore_mp();

	std::cout << "Shop item list\n";

	if (attack_left >= 1)
		std::cout << "1. Attack +10 (700 Gold) (Available)" << std::endl;
	else // when attack_item is solded out
		std::cout << "1. Attack +10 (700 Gold) (Sold out)" << std::endl;


	if (defense_left >= 1)
		std::cout << "2. Defense +5 (700 Gold) (Available)" << std::endl;
	else // when defense_item is solded out
		std::cout << "2. Defense +5 (700 Gold) (Sold out)" << std::endl;


	if (exp_left >= 1)
		std::cout << "3. Exp +300 (700 Gold) (Available)" << std::endl;
	else // when exp_item is solded out
		std::cout << "3. Exp +300 (700 Gold) (Sold out)" << std::endl;


	std::cout << "4. Restore HP (500 Gold) (Always available)\n";
	std::cout << "5. Restore MP (500 Gold) (Always available)\n";
	std::cout << "=====================================================\n" << std::endl;
	return 6;
}