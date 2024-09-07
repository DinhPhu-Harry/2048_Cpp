#include"menu.h"

void menu() {
	cout << "\n==========MENU=========\n" << endl;
	cout << "1. New Game" << endl;
	cout << "2. Resume" << endl;
	cout << "3. Game settings" << endl;
	cout << "4. Top-20 list" << endl;
	cout << "\n=======================\n";
}
void menuSetting() {
	cout << "\nBan muon cai dat chuc nang gi?" << endl;
	cout << "1. Lua chon map 4x4 -> 10x10" << endl;
	cout << "2. Lua chon tat/mo chuc nang Undo/Redo" << endl;
}
void menuMap() {
	cout << "\nBan muon choi che do nao?" << endl;
	cout << "1. 4 x 4" << endl;
	cout << "2. 5 x 5" << endl;
	cout << "3. 6 x 6" << endl;
	cout << "4. 7 x 7" << endl;
	cout << "5. 8 x 8" << endl;
	cout << "6. 9 x 9" << endl;
	cout << "7. 10 x 10" << endl;
}

void menuUndoRedo() {
	cout << "\nBan co muon mo chuc nang undo/redo khong?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;
}