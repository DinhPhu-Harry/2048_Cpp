#pragma once
#include"Player.h"

void saveGameState(Player* player, int board[10][10], int score);	//Hàm lưu trạng thái của bảng game

void loadGameState(Player* player, int board[10][10], int& score);	//Hàm tải lại trạng thái của bảng game