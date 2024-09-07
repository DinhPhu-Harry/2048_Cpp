#pragma once
#include"Player.h"
#include"PlayerList.h"
#include<conio.h>
#include"2048.h"

void managePlayerSave(Player* player);
void gameLoopSave_with_Undo(Player* player, int n, PlayerList*& l);           //Hàm chơi game đã lưu trước đó với chức năng Undo/Redo
void gameLoopSave_without_Undo(Player* player, int n, PlayerList*& l);		//Hàm chơi game đã lưu trước đó nhưng không có chức năng Undo/Redo
