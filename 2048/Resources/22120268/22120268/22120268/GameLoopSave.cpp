#include"GameLoopSave.h"
#include"WriteFile.h"
#include"ReadFile.h"
#include"SaveGame.h"
//#include"ReadFile.h"
#include"Color.h"

void managePlayerSave(Player* player) {
    PlayerList* players = readPlayersFromFile();

    if (players->size < 5) {
        addTail(players, player);
    }
    else {
        SetColor(White, Red);
        cout << "Danh sach nguoi choi da day, ban phai thay the 1 nguoi choi trong so 5 nguoi choi hien co." << endl;
        SetColor(White, Black);
        int index = 1;
        PlayerNode* temp = players->head;
        while (temp != nullptr) {
            cout << index << ". " << temp->_player->playerName << " - Diem: " << temp->_player->score << endl;
            temp = temp->next;
            index++;
        }
        int choice;
        cout << "Chon so cua nguoi choi de thay the: ";
        cin >> choice;
        while (choice < 1 || choice > 5) {
            cout << "Lua chon khong hop le, vui long chon lai: ";
            cin >> choice;
        }
        PlayerNode* prev = nullptr;
        temp = players->head;
        for (int i = 1; i < choice; ++i) {
            prev = temp;
            temp = temp->next;
        }
        PlayerNode* newNode = new PlayerNode;
        newNode->_player = player;
        newNode->next = temp->next;
        if (prev == nullptr) {
            players->head = newNode;
        }
        else {
            prev->next = newNode;
        }
        delete temp->_player;
        delete temp;
    }

    savePlayersToFile(players);
    // Thu hồi bộ nhớ đã cấp phát cho danh sách liên kết
    PlayerNode* current = players->head;
    while (current != nullptr) {
        PlayerNode* next = current->next;
        delete current->_player;
        delete current;
        current = next;
    }
    delete players;
}

void gameLoopSave_with_Undo(Player* player, int n, PlayerList*& l) {
    int score = player->score;
    char move;
    Stack<GameState> historyStack;
    Stack<GameState> redoStack;

    srand(time(0));
    addblock(player->gameState.board, n);
    addblock(player->gameState.board, n);

    while (true) {
        system("cls");
        disp(player->gameState.board, n, score);

        cout << "Nhan cac nut di chuyen (WASD) hoac phim 'U' de undo hoac 'R' de redo hoac phim 'E' de thoat" << endl;
        move = _getch();

        if (move == 'E' || move == 'e') {
            cout << "Ban co chac muon thoat tro choi khong? (Nhan 1 hoac 2)" << endl;
            cout << "1. Co" << endl;
            cout << "2. Khong" << endl;
            int n = 0;
            cin >> n;
            while (n != 1 && n != 2) {
                system("cls");
                cout << "Khong hop le!! Nhap lai: ";
                cout << "Ban co chac muon thoat tro choi khong? (Nhan 1 hoac 2)" << endl;
                cout << "1. Co" << endl;
                cout << "2. Khong" << endl;
                cin >> n;
            }
            if (n == 1) {
                saveGameState(player, player->gameState.board, score);
                cout << "Tro choi da duoc luu, dang thoat..." << endl;
                system("pause");
                break;
            }
        }

        if (move == 'U' || move == 'u') {
            if (!historyStack.empty()) {
                redoStack.push({ 0 });
                memcpy(redoStack.top().board, player->gameState.board, sizeof(player->gameState.board));
                redoStack.top().score = score;

                GameState previousState = historyStack.top();
                historyStack.pop();
                memcpy(player->gameState.board, previousState.board, sizeof(player->gameState.board));
                score = previousState.score;
            }
            continue;
        }

        if (move == 'R' || move == 'r') {
            if (!redoStack.empty()) {
                historyStack.push({ 0 });
                memcpy(historyStack.top().board, player->gameState.board, sizeof(player->gameState.board));
                historyStack.top().score = score;

                GameState redoState = redoStack.top();
                redoStack.pop();
                memcpy(player->gameState.board, redoState.board, sizeof(player->gameState.board));
                score = redoState.score;
            }
            continue;
        }

        historyStack.push({ 0 });
        memcpy(historyStack.top().board, player->gameState.board, sizeof(player->gameState.board));
        historyStack.top().score = score;

        while (!redoStack.empty()) redoStack.pop();

        switch (move) {
        case 'W':
        case 'w':
            upmove(player->gameState.board, n, score);
            break;
        case 'S':
        case 's':
            downmove(player->gameState.board, n, score);
            break;
        case 'A':
        case 'a':
            leftmove(player->gameState.board, n, score);
            break;
        case 'D':
        case 'd':
            rightmove(player->gameState.board, n, score);
            break;
        default:
            cout << "Khong hop le! nhan cac nut W, A, S, D, U, R, or E." << endl;
            historyStack.pop();
            continue;
        }

        if (!historyStack.empty() && !check(historyStack.top().board, player->gameState.board, n)) {
            addblock(player->gameState.board, n);
        }

        if (!checkover(player->gameState.board, n)) {
            cout << "Game Over! Diem cua ban la " << score << endl;
            break;
        }
    }

    player->score = score;
    addTail(l, player);
    savePlayersToFile(l);
    //managePlayerSave(player);
}

void gameLoopSave_without_Undo(Player* player, int n, PlayerList*& l) {
    int score = player->score;
    char move;

    srand(time(0));
    addblock(player->gameState.board, n);
    addblock(player->gameState.board, n);

    while (true) {
        system("cls");
        disp(player->gameState.board, n, score);

        cout << "Nhan cac phim (WASD) de di chuyen hoac 'E' de thoat tro choi" << endl;
        move = _getch();

        if (move == 'E' || move == 'e') {
            cout << "Ban co chac muon thoat tro choi khong? (Nhan 1 hoac 2)" << endl;
            cout << "1. Co" << endl;
            cout << "2. Khong" << endl;
            int n = 0;
            cin >> n;
            while (n != 1 && n != 2) {
                system("cls");
                cout << "Lua chon khong hop le. chon lai: ";
                cout << "Ban co chac muon thoat tro choi khong? (Nhan 1 hoac 2)" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cin >> n;
            }
            if (n == 1) {
                saveGameState(player, player->gameState.board, score);
                cout << "Game saved. Exiting..." << endl;
                system("pause");
                break;
            }
        }

        switch (move) {
        case 'W':
        case 'w':
            upmove(player->gameState.board, n, score);
            break;
        case 'S':
        case 's':
            downmove(player->gameState.board, n, score);
            break;
        case 'A':
        case 'a':
            leftmove(player->gameState.board, n, score);
            break;
        case 'D':
        case 'd':
            rightmove(player->gameState.board, n, score);
            break;
        default:
            cout << "Khong hop le! Nhan cac phim W, A, S, D, or E." << endl;
            continue;
        }
        addblock(player->gameState.board, n);
        if (!checkover(player->gameState.board, n)) {
            cout << "Game Over! Diem cua ban la " << score << endl;
            break;
        }
    }

    player->score = score;
    addTail(l, player);
    savePlayersToFile(l);
    //managePlayerSave(player);
}
