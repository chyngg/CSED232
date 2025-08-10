#include "Map.h"
#include "Character.h"
#include "Monster.h"
#include "Shop.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>

Map::Map() 
{
	char init_mapping[8][8] = { {'E', 'R', 'M', 'M', 'R', 'E', 'M', 'M'},
		{'M', 'E', 'R', 'E', 'M', 'R', 'E', 'R'},
		{'R', 'M', 'E', 'E', 'M', 'E', 'M', 'M'},
		{'M', 'E', 'R', 'S', 'M', 'M', 'E', 'R'},
		{'M', 'M', 'E', 'R', 'E', 'R', 'M', 'E'},
		{'E', 'R', 'M', 'E', 'M', 'E', 'E', 'R'},
		{'M', 'E', 'R', 'M', 'M', 'E', 'R', 'M'},
		{'E', 'E', 'M', 'E', 'R', 'M', 'E', 'B'} }; // initial map data
	std::copy(&init_mapping[0][0], &init_mapping[0][0] + 8 * 8, &mapping[0][0]);
	memset(visit, 0, sizeof(visit)); // make all elements of visit[8][8] to 0
	visit[0][0] = 1; // start point -> visited
}

Map::~Map() {}

void Map::show_map(Character &ch) {
	using namespace std;
	char map_shown[8][8]; // map shown in terminal
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == ch.y && j == ch.x)
				map_shown[i][j] = 'y';
			else if (visit[i][j] == 0) // unvisited room
				map_shown[i][j] = '?';
			else // visited room
				map_shown[i][j] = ' ';
		}
	}
	
	cout << "\n忙式式式成式式式成式式式成式式式成式式式成式式式成式式式成式式式忖" << endl;
	for (int i = 0; i < 8; i++) {
		cout << "弛";
		for (int j = 0; j < 8; j++) {
			if (map_shown[i][j] == 'y')
				cout << "You";
			else
				cout << setw(2) << map_shown[i][j] << setw(3);
			cout << "弛";
		}
		cout << endl;
		if (i < 7)
			cout << "戍式式式托式式式托式式式托式式式托式式式托式式式托式式式托式式式扣" << endl;
	}
	cout << "戌式式式扛式式式扛式式式扛式式式扛式式式扛式式式扛式式式扛式式式戎" << endl;
	return;
}

int Map::move(Character &ch, Shop &shop) {
	int defeat_boss = 0; // Whether you clear the game
	int can_move = 0; // If you can move to the direction you want, 1 is assigned
	std::cout << "Where do you want to go?" << std::endl;
	while (can_move == 0)
	{
		char where_to_move = 'p';
		while (where_to_move != 'a' && where_to_move != 'w' && where_to_move != 's' && where_to_move != 'd') {
			std::cout << "> ";
			std::cin >> where_to_move;
		}
		
		if (where_to_move == 'w')
			can_move = go_up(ch); // 
		else if (where_to_move == 's')
			can_move = go_down(ch);
		else if (where_to_move == 'a')
			can_move = go_left(ch);
		else
			can_move = go_right(ch);
	}

	visit[ch.y][ch.x] = 1; // mark the room you visited
	
	if (mapping[ch.y][ch.x] == 'R') { // random room
		std::cout << "Random encounter!\n" << std::endl;
		ch.random_room();
		mapping[ch.y][ch.x] = 'E';
	}
	else if (mapping[ch.y][ch.x] == 'M') { // meet monster
		std::cout << "\nWild monster appeared!\n\n";
		int survive = 1;
		Monster monster(ch.x + ch.y);
		survive = monster.fight(ch);
		if (survive == 0) // If you die by monster
			return 5;
		mapping[ch.y][ch.x] = 'E'; // after you fight with monster, the room changes to the empty room
	}
	else if (mapping[ch.y][ch.x] == 'S') { // shop
		shop.select(ch);
	}
	else if (mapping[ch.y][ch.x] == 'B') { // boss
		int survive;
		Monster monster(ch.x + ch.y);
		monster.boss();
		survive = monster.fight_boss(ch);
		if (survive == 0) // when you didn't defeat the boss

			return 5;
		else
			defeat_boss = 4; // when you defeat the boss
	}

	return defeat_boss;
}

int Map::go_up(Character &ch) { 
	if (ch.y == 0) {
		std::cout << "You cannot move to that direction." << std::endl;
		return 0;
	}

	ch.y--;
	return 1;
}

int Map::go_down(Character &ch) {
	if (ch.y == 7) {
		std::cout << "You cannot move to that direction." << std::endl;
		return 0;
	}

	ch.y++;
	return 1;
}

int Map::go_left(Character &ch) {
	if (ch.x == 0) {
		std::cout << "You cannot move to that direction." << std::endl;
		return 0;
	}

	ch.x--;
	return 1;
}

int Map::go_right(Character &ch) {
	if (ch.x == 7) {
		std::cout << "You cannot move to that direction." << std::endl;
		return 0;
	}

	ch.x++;
	return 1;
}

int Map::ready(Character &ch) {
	using namespace std;
	show_map(ch);
	cout << "1. Choose direction" << endl;
	cout << "2. Show character status" << endl;
	cout << "3. Exit game\n> ";

	int what_to_do = 0;
	do {
		cin >> what_to_do;
	} while (what_to_do < 1 || what_to_do > 3);

	return what_to_do;
}
