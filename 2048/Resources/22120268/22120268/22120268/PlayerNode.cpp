#include "PlayerNode.h"
PlayerNode* creatNode(Player* player) {
	PlayerNode* temp = new PlayerNode;
	temp->next = nullptr;
	temp->_player = player;
	return temp;
}