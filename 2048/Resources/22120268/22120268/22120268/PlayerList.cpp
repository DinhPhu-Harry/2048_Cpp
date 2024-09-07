#include "PlayerList.h"


void InitList(PlayerList*& l) {    //hàm khởi tạo dslk
	l->head = nullptr;
	l->size = 0;
}

void printList(PlayerList* l) {
	if (l->head == nullptr) {
		cout << "Danh sach nguoi choi rong" << endl;
		return;
	}

	PlayerNode* node = l->head;
	for (int i = 0; i < l->size; i++) {
		//cout << i << endl;
		cout << "Name: " << node->_player->playerName << " - " << "Score: " << node->_player->score << endl;
		node = node->next;
	}
}


void addTail(PlayerList*& l, Player* player) {
	PlayerNode* newNode = new PlayerNode{ player, nullptr };
	if (l->head == nullptr) {
		l->head = newNode;
	}
	else {
		PlayerNode* temp = l->head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	l->size++;
}


void deleteNode(PlayerList*& l, Player* node)  //hàm xóa node
{
	if (l->head == nullptr) {							//dslk rong thi bao loi roi thoat ra
		cout << "Khong co node nao de xoa" << endl;
		return;
	}
	else {
		PlayerNode* temp = creatNode(node);
		if (temp == l->head) {                      //Node can xoa la node dau tien: head
			PlayerNode* temp2 = l->head;			
			l->head = l->head->next;					//Gan head la node phia sau

			temp2->next = nullptr;					//thuc hien xoa node
			delete temp2;
			temp2 = nullptr;
		}
		else {				//Node cần xóa không phải head
			PlayerNode* cur = l->head->next;		//Tạo một node tạm để luu node hiện tại
			PlayerNode* prev = l->head;             //Tạo biến tạm để lưu node trước đó
			while (cur != nullptr) {			//duyệt qua danh sách liên kết đến node cần xóa
				if (cur == temp) {
					PlayerNode* temp2 = cur;
					prev->next = cur->next;					//Gan head la node phia sau

					cur->next = nullptr;					//thuc hien xoa node
					delete cur;
					cur = nullptr;
				}

				prev = cur;
				cur = cur->next;
			}
		}
		l->size--;
	}
}