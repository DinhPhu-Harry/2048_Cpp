#include"ReadFile.h"

PlayerList* readPlayersFromFile() {
    ifstream inFile("saved_games.bin", ios::binary);
    PlayerList* players = new PlayerList;
    InitList(players);
    if (!inFile) {
        cout << "Error: Khong the mo file de doc!" << endl;
        return players; // Trả về danh sách rỗng nếu không thể mở tệp
    }
    inFile.read((char*)&players->size, sizeof(players->size));
    int sizeofPlayers = players->size;
    for (int i = 0; i < sizeofPlayers; i++) {
        Player* player = new Player;
        size_t nameLen;
        inFile.read((char*)&nameLen, sizeof(nameLen));
        player->playerName.resize(nameLen);
        inFile.read(&player->playerName[0], nameLen);
        inFile.read((char*)&player->score, sizeof(player->score));
        inFile.read((char*)&player->gameState, sizeof(player->gameState));
        addTail(players, player);
    }
    inFile.close();
    return players;
}