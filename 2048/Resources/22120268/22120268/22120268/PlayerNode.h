#pragma once
#include"Player.h"

struct PlayerNode
{
	Player* _player;
	PlayerNode* next;
};

PlayerNode* creatNode(Player* player);
