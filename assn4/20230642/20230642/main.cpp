#include <iostream>
#include <cstdlib>
#include "Character.h"
#include "Map.h"
#include "Monster.h"
#include "Shop.h"
void show_init();
int clear = 0;
int main()
{
	using namespace std;
	show_init();
	int start = 0;
	while (start != 1 && start != 2) {
		cout << "> ";
		cin >> start;
	}
		
	if (start == 2) {
		cout << "Exit..." << endl;
		return 0;
	}
	cout << "Game start!" << endl;
	Character character; // create character
	Map map; // create map
	Shop shop; // create shop
	while (clear >= 0 && clear <= 3)
	{
		clear = map.ready(character);
		if (clear == 1) { // If you want to move
			clear = map.move(character, shop);
			if (clear == 5) // If you died by monster
				return 0;
		}
		else if (clear == 2) { // If you want to see character status
			character.show_status();
		}
		else if (clear == 3) { // If you want to exit the game
			cout << "Exit..." << endl;
			return 0;
		}


		if (clear == 4) { // If you defeat a boss monster
			cout << "Congratulations! You cleared the game!" << endl;
			cout << "See you next time!" << endl;
			return 0;
		}
	}
		 
}

void show_init()
{
	std::cout << "========================================================" << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << " #######                      ######  ######   ##### " << std::endl;
	std::cout << "    #    ###### #    # #####  #     # #     # #     # " << std::endl;
	std::cout << "    #    #       #  #    #    #     # #     # # " << std::endl;
	std::cout << "    #    #####    ##     #    ######  ######  #  #### " << std::endl;
	std::cout << "    #    #        ##     #    #   #   #       #     #" << std::endl;
	std::cout << "    #    #       #  #    #    #    #  #       #     # " << std::endl;
	std::cout << "    #    ###### #    #   #    #     # #        ##### " << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "========================================================" << std::endl;

	std::cout << "----- Menu -----" << std::endl;
	std::cout << "1. Start game\n";
	std::cout << "2. Exit\n";
	return;

}

