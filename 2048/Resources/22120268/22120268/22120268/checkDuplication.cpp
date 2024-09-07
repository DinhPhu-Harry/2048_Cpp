#include"checkDuplication.h"

bool checkDuplication(PlayerList* l, Player* player) {
    PlayerNode* temp = l->head;
    while (temp != nullptr) {
        if (temp->_player->playerName == player->playerName) {
            return false;
        }
        temp = temp->next;
    }
    return true;
}