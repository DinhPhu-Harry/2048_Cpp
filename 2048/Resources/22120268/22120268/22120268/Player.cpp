#include "Player.h"
#include<string>

Player* inputPlayer() {
	Player* player = new Player;
	cout << "Nhap ten: ";
	cin.ignore();
	getline(cin, player->playerName);
	player->score = 0;
	return player;
}

