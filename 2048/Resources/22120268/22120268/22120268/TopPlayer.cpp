#include"TopPlayer.h"

void saveTopPlayersToFile(PlayerList* l) {
    ofstream outFile("top_players.bin", ios::binary);
    if (!outFile) {
        cout << "Error: Khong the mo file de ghi!" << endl;
        return;
    }

    // Đếm số lượng người chơi trong danh sách liên kết
    PlayerNode* temp = l->head;
    int count = 0;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }

    // Tạo một mảng động để lưu người chơi tạm thời
    Player** players = new Player * [count];
    temp = l->head;
    int index = 0;
    while (temp != nullptr) {
        players[index++] = temp->_player;
        temp = temp->next;
    }

    // Sắp xếp mảng theo điểm số giảm dần
    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (players[i]->score < players[j]->score) {
                Player* tempPlayer = players[i];
                players[i] = players[j];
                players[j] = tempPlayer;
            }
        }
    }

    // Giới hạn danh sách chỉ còn 20 người chơi cao điểm nhất
    int size = (count < 20) ? count : 20;
    outFile.write((char*)&size, sizeof(size));

    for (int i = 0; i < size; ++i) {
        Player* player = players[i];
        size_t nameLen = player->playerName.size();
        outFile.write((char*)&nameLen, sizeof(nameLen));
        outFile.write(player->playerName.c_str(), nameLen);
        outFile.write((char*)&player->score, sizeof(player->score));
        outFile.write((char*)&player->gameState, sizeof(player->gameState));
    }

    // Giải phóng bộ nhớ mảng động
    delete[] players;
    outFile.close();
}

PlayerList* readTopPlayersFromFile() {
    PlayerList* players = new PlayerList;
    InitList(players);

    ifstream inFile("top_players.bin", ios::binary);
    if (!inFile) {
        cout << "Error: Khong the mo file de doc!" << endl;
        return players;
    }

    int size;
    inFile.read((char*)&size, sizeof(size));

    for (int i = 0; i < size; ++i) {
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
