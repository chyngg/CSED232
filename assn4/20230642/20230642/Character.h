#pragma once
class Character {
private:
	int max_hp=100;
	int max_mp=20;
	int max_exp=100;
	int level=1;

public:
	int gold=0;
	int attack=10;
	int defense=2;
	int curr_hp=100;
	int curr_mp=20;
	int curr_exp=0;
	int x=0;
	int y=0;
	
	Character() // Constructor -> initialize member values
	{
		max_hp = 100;
		max_mp = 20;
		max_exp = 100;
		level = 1;
		gold = 0;
		attack = 10;
		defense = 2;
		curr_hp = 100;
		curr_mp = 20;
		curr_exp = 0;
		x = 0;
		y = 0;
	}
	~Character() {}

	void show_status();
	void random_room();
	void check_level(int exp);
	void print_level_up(int exp);
	void print_state(int exp);
	void two_level_up(int exp);
	void enter_shop();

	void buy_attack();
	void buy_defense();
	void restore_hp();
	void restore_mp();
};