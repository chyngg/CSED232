#pragma once
class Character;

class Shop {
private:
	int attack_left;
	int defense_left;
	int exp_left;
public:
	Shop();
	~Shop();

	void select(Character &ch);
	int item_attack(Character &ch);
	int item_defense(Character &ch);
	int item_exp(Character &ch);
	int item_hp(Character &ch);
	int item_mp(Character &ch);
};
