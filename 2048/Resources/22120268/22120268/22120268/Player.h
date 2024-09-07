#pragma once
#include<iostream>
#include"GameState.h"
using namespace std;

struct Player {
	string playerName;
	int score;
	GameState gameState;
};

Player* inputPlayer();
