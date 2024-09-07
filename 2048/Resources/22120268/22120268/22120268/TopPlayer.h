#pragma once
#include"PlayerList.h"
#include<fstream>
#include<vector>
#include<algorithm>

void saveTopPlayersToFile(PlayerList* l);
PlayerList* readTopPlayersFromFile();
