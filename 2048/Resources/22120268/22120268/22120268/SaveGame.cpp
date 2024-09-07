#include"SaveGame.h"

void saveGameState(Player* player, int board[10][10], int score) {
    memcpy(player->gameState.board, board, sizeof(int) * 10 * 10);
    player->gameState.score = score;
}

void loadGameState(Player* player, int board[10][10], int& score) {
    memcpy(board, player->gameState.board, sizeof(int) * 10 * 10);
    score = player->gameState.score;
}