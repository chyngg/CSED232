#pragma once
class Character;
class Shop;
class Map {
private:
	char mapping[8][8];
	int visit[8][8];
public:
	Map();
	~Map();
	
	void show_map(Character &ch);
	int move(Character &ch, Shop &shop);
	int go_up(Character &ch);
	int go_down(Character &ch);
	int go_left(Character &ch);
	int go_right(Character &ch);

	int ready(Character &ch);
};
