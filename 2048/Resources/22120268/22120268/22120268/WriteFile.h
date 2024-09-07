#pragma once
#include"PlayerList.h"
#include"Player.h"'
#include<fstream>

const int MAX_SAVED_GAMES = 5;

void savePlayersToFile(PlayerList* l);