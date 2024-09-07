#pragma once
#include"WriteFile.h"
#include"SaveGame.h"
#include<conio.h>

void gameLoop_with_Undo(Player* player, int n, PlayerList*&l) {
    int board[10][10] = { 0 };
    int score = 0;
    char move;
    Stack<GameState> historyStack;
    Stack<GameState> redoStack;

    srand(time(0));
    addblock(board, n);
    addblock(board, n);

    while (true) {
        system("cls");
        disp(board, n, score);

        cout << "Enter move (WASD) or 'U' for undo or 'R' for redo or 'E' to exit" << endl;
        move = _getch();

        if (move == 'E' || move == 'e') {
            cout << "Are you sure to exit the game?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            int n = 0;
            cin >> n;
            while (n != 1 && n != 2) {
                system("cls");
                cout << "Khong hop le!! Nhap lai: ";
                cout << "Are you sure to exit the game?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cin >> n;
            }
            if (n == 1) {
                saveGameState(player, board, score);
                cout << "Game saved. Exiting..." << endl;
                system("pause");
                break;
            }
        }

        if (move == 'U' || move == 'u') {
            if (!historyStack.empty()) {
                redoStack.push({ 0 });
                memcpy(redoStack.top().board, board, sizeof(board));
                redoStack.top().score = score;

                GameState previousState = historyStack.top();
                historyStack.pop();
                memcpy(board, previousState.board, sizeof(board));
                score = previousState.score;
            }
            continue;
        }

        if (move == 'R' || move == 'r') {
            if (!redoStack.empty()) {
                historyStack.push({ 0 });
                memcpy(historyStack.top().board, board, sizeof(board));
                historyStack.top().score = score;

                GameState redoState = redoStack.top();
                redoStack.pop();
                memcpy(board, redoState.board, sizeof(board));
                score = redoState.score;
            }
            continue;
        }

        historyStack.push({ 0 });
        memcpy(historyStack.top().board, board, sizeof(board));
        historyStack.top().score = score;

        while (!redoStack.empty()) redoStack.pop();

        switch (move) {
        case 'W':
        case 'w':
            upmove(board, n, score);
            break;
        case 'S':
        case 's':
            downmove(board, n, score);
            break;
        case 'A':
        case 'a':
            leftmove(board, n, score);
            break;
        case 'D':
        case 'd':
            rightmove(board, n, score);
            break;
        default:
            cout << "Invalid move! Please enter W, A, S, D, U, R, or E." << endl;
            historyStack.pop();
            continue;
        }

        if (!historyStack.empty() && !check(historyStack.top().board, board, n)) {
            addblock(board, n);
        }

        if (!checkover(board, n)) {
            cout << "Game Over! Your score is " << score << endl;
            break;
        }
    }

    player->score = score;
    addTail(l, player);
    savePlayersToFile(l);
}

void gameLoop_without_Undo(Player* player, int n, PlayerList*& l) {
    int board[10][10] = { 0 };
    int score = 0;
    char move;

    srand(time(0));
    addblock(board, n);
    addblock(board, n);

    while (true) {
        system("cls");
        disp(board, n, score);

        cout << "Enter move (WASD) or 'E' to exit" << endl;
        move = _getch();

        if (move == 'E' || move == 'e') {
            cout << "Are you sure to exit the game?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            int n = 0;
            cin >> n;
            while (n != 1 && n != 2) {
                system("cls");
                cout << "Invalid input!! Please re-enter: ";
                cout << "Are you sure to exit the game?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cin >> n;
            }
            if (n == 1) {
                saveGameState(player, board, score);
                cout << "Game saved. Exiting..." << endl;
                system("pause");
                break;
            }
        }

        switch (move) {
        case 'W':
        case 'w':
            upmove(board, n, score);
            break;
        case 'S':
        case 's':
            downmove(board, n, score);
            break;
        case 'A':
        case 'a':
            leftmove(board, n, score);
            break;
        case 'D':
        case 'd':
            rightmove(board, n, score);
            break;
        default:
            cout << "Invalid move! Please enter W, A, S, D, or E." << endl;
            continue;
        }
        addblock(board, n);
        if (!checkover(board, n)) {
            cout << "Game Over! Your score is " << score << endl;
            break;
        }
    }

    player->score = score;
    addTail(l, player);
    savePlayersToFile(l);
}
