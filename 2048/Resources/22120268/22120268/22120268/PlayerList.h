#pragma once
#include"PlayerNode.h"

struct PlayerList{
	PlayerNode* head;
	int size;
};

void InitList(PlayerList*& l);
void printList(PlayerList* l);
void addTail(PlayerList*& l, Player* player);
void deleteNode(PlayerList*& l, Player* node);