#include"WriteFile.h"

void savePlayersToFile(PlayerList* l) {
    ofstream outFile("saved_games.bin", ios::binary);
    if (!outFile) {
        cout << "Error: khong the mo file de luu!" << endl;
        return;
    }
    outFile.write((char*)&l->size, sizeof(l->size));
    PlayerNode* temp = l->head;
    while (temp != nullptr) {
        size_t nameLen = temp->_player->playerName.size();
        outFile.write((char*)&nameLen, sizeof(nameLen));
        outFile.write(temp->_player->playerName.c_str(), nameLen);
        outFile.write((char*)&temp->_player->score, sizeof(temp->_player->score));
        outFile.write((char*)&temp->_player->gameState, sizeof(temp->_player->gameState));
        temp = temp->next;
    }
    outFile.close();
}
