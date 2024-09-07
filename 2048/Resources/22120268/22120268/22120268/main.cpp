#include"main.h"
#include"ReadFile.h"
#include"TopPlayer.h"
#include"checkDuplication.h"

int main() {
	int choiceUndoRedo = 2;
	int mapsize = 4;
	int choice = -1;
	PlayerList* l = new PlayerList;
	InitList(l);

	do {
		system("cls");
		menu();
		cout << "Nhap lua chon cua ban: ";
		cin >> choice;
		while (choice <= 0 || choice > 4) {
			cout << "Lua chon khong hop le. vui long nhap lai: ";
			cin >> choice;
		}

		switch (choice) {
		case 1: {
			Player* player1 = inputPlayer();
			PlayerList* l = readTopPlayersFromFile();
			while (true) {
				if (checkDuplication(l, player1) == false) {
					cout << "Ten nay da co tu truoc. Vui long chon ten khac: " << endl;
					cout << "Nhap ten: ";
					getline(cin, player1->playerName);
				}
				else {
					break;
				}

			}
			if (choiceUndoRedo == 1) {
				gameLoop_with_Undo(player1, mapsize, l);
			}
			else
				gameLoop_without_Undo(player1, mapsize, l);
			saveTopPlayersToFile(l);
			break;
		}
		case 2: {
			PlayerList* savedPlayers = readPlayersFromFile();
			if (savedPlayers->head == nullptr) {
				cout << "Khong co game nao duoc luu truoc do " << endl;
				system("pause");
			}
			else {
				cout << "Chon mot tai khoan de choi tiep " << endl;
				PlayerNode* temp = savedPlayers->head;
				int index = 1;
				while (temp != nullptr) {
					cout << index << ". " << temp->_player->playerName << " - Diem: " << temp->_player->score << endl;
					temp = temp->next;
					index++;
				}
				int choiceResume;
				cout << "Nhap lua chon cua ban: ";
				cin >> choiceResume;
				while (choiceResume <= 0 || choiceResume >= index) {
					cout << "Lua chon khong hop le. Vui long chon lai ";
					cin >> choiceResume;
				}
				temp = savedPlayers->head;
				for (int i = 1; i < choiceResume; ++i) {
					temp = temp->next;
				}
				Player* chosenPlayer = temp->_player;
				disp(temp->_player->gameState.board, 4, temp->_player->score);
				if (choiceUndoRedo == 1) {
					gameLoopSave_with_Undo(chosenPlayer, mapsize, l);
				}
				else {
					gameLoopSave_without_Undo(chosenPlayer, mapsize, l);
				}
				saveTopPlayersToFile(l);
			}

			break;
		}
		case 3: {
			int choiceSetting = 0;
			menuSetting();
			cout << "Nhap lua chon cua ban: ";
			cin >> choiceSetting;
			while (choiceSetting != 1 && choiceSetting != 2) {
				cout << "Lua chon khong hop le, vui long chon lai " << endl;
				cin >> choiceSetting;
			}

			if (choiceSetting == 1) {

				int choiceMap = 0;
				do {
					menuMap();

					cout << "Nhap lua chon cua ban: ";
					cin >> choiceMap;
				} while (choiceMap < 1 || choiceMap > 7);
				if (choiceMap == 1) mapsize = 4;
				else if (choiceMap == 2) mapsize = 5;
				else if (choiceMap == 3) mapsize = 6;
				else if (choiceMap == 4) mapsize = 7;
				else if (choiceMap == 5) mapsize = 8;
				else if (choiceMap == 6) mapsize = 9;
				else if (choiceMap == 7) mapsize = 10;
			}
			else {
				menuUndoRedo();
				do {
					cout << "Nhap lua chon cua ban: ";
					cin >> choiceUndoRedo;
				} while (choiceUndoRedo != 1 && choiceUndoRedo != 2);
			}
			break;
		}
		case 4: {
			PlayerList* l1 = new PlayerList;
			//InitList(l1);

			l1 = readTopPlayersFromFile();
			printList(l1);

			system("pause");
			for (PlayerNode* temp = l1->head; temp != nullptr; )
			{
				PlayerNode* next = temp->next;
				delete temp->_player;
				delete temp;
				temp = next;
			}
			delete l1;  //Thu hồi vùng nhớ cho danh sách liên kết
			l1 = nullptr;
			break;
		}
		}
	} while (true);


	for (PlayerNode* temp = l->head; temp != nullptr; )
	{
		PlayerNode* next = temp->next;
		delete temp->_player;
		delete temp;
		temp = next;
	}
	delete l;  //Thu hồi vùng nhớ cho danh sách liên kết
	l = nullptr;
	return 0;
}
