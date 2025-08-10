#pragma once
class Character;
enum source { fire = 1, grass = 2, water = 3, nothing = 4 };

class Monster {
private:
	int difficulty = 0;
	int init_hp;
	int curr_hp;
	int attack;
	int defense;
	int reward_gold;
	int reward_exp;
	source type;

public:
	Monster(int difficulty);
	~Monster();
	
	int fight(Character &ch);
	void show_monster_state();

	void attack_basic(Character &ch);
	void attack_skill(Character &ch);
	void attack_fire(Character &ch);
	void attack_grass(Character &ch);
	void attack_water(Character &ch);

	void attack_by_monster(Character &ch);

	void boss();
	int fight_boss(Character &ch);

};
