#include"2048.h"


void upmove(int a[][10], int n, int& score) {
    int i, j, li, ri;
    for (j = 0; j < n; j++) {
        li = 0, ri = j;
        for (i = 1; i < n; i++) {
            if (a[i][j] != 0) {
                if (a[i - 1][j] == 0 || a[i - 1][j] == a[i][j]) {
                    if (a[li][ri] == a[i][j]) {
                        a[li][ri] *= 2;
                        score += a[li][ri];
                        a[i][j] = 0;
                    }
                    else {
                        if (a[li][ri] == 0) {
                            a[li][ri] = a[i][j];
                            a[i][j] = 0;
                        }
                        else {
                            a[++li][ri] = a[i][j];
                            a[i][j] = 0;
                        }
                    }
                }
                else li++;
            }
        }
    }
}

void downmove(int a[][10], int n, int& score) {
    int i, j, li, ri;
    for (j = 0; j < n; j++) {
        li = n - 1, ri = j;
        for (i = n - 2; i >= 0; i--) {
            if (a[i][j] != 0) {
                if (a[i + 1][j] == 0 || a[i + 1][j] == a[i][j]) {
                    if (a[li][ri] == a[i][j]) {
                        a[li][ri] *= 2;
                        score += a[li][ri];
                        a[i][j] = 0;
                    }
                    else {
                        if (a[li][ri] == 0) {
                            a[li][ri] = a[i][j];
                            a[i][j] = 0;
                        }
                        else {
                            a[--li][ri] = a[i][j];
                            a[i][j] = 0;
                        }
                    }
                }
                else li--;
            }
        }
    }
}

void leftmove(int a[][10], int n, int& score) {
    int i, j, li, ri;
    for (i = 0; i < n; i++) {
        li = i, ri = 0;
        for (j = 1; j < n; j++) {
            if (a[i][j] != 0) {
                if (a[i][j - 1] == 0 || a[i][j - 1] == a[i][j]) {
                    if (a[li][ri] == a[i][j]) {
                        a[li][ri] *= 2;
                        score += a[li][ri];
                        a[i][j] = 0;
                    }
                    else {
                        if (a[li][ri] == 0) {
                            a[li][ri] = a[i][j];
                            a[i][j] = 0;
                        }
                        else {
                            a[li][++ri] = a[i][j];
                            a[i][j] = 0;
                        }
                    }
                }
                else ri++;
            }
        }
    }
}

void rightmove(int a[][10], int n, int& score) {
    int i, j, li, ri;
    for (i = 0; i < n; i++) {
        li = i, ri = n - 1;
        for (j = n - 2; j >= 0; j--) {
            if (a[i][j] != 0) {
                if (a[i][j + 1] == 0 || a[i][j + 1] == a[i][j]) {
                    if (a[li][ri] == a[i][j]) {
                        a[li][ri] *= 2;
                        score += a[li][ri];
                        a[i][j] = 0;
                    }
                    else {
                        if (a[li][ri] == 0) {
                            a[li][ri] = a[i][j];
                            a[i][j] = 0;
                        }
                        else {
                            a[li][--ri] = a[i][j];
                            a[i][j] = 0;
                        }
                    }
                }
                else ri--;
            }
        }
    }
}

void addblock(int a[][10], int n) {
    int li, ri;
    srand(time(0));
    while (true) {
        li = rand() % n;
        ri = rand() % n;
        if (a[li][ri] == 0) {
            a[li][ri] = pow(2, li % 2 + 1);
            break;
        }
    }
}

void disp(const int a[][10], int n, int score) {
    cout << "\n\t\tNhan phim E de thoat game ";
    cout << "\n\t\tDiem: " << score;
    cout << "\n\n\n\n";
    int i, j;
    for (i = 0; i < n; i++) {
        cout << "\t\t\t\t";
        for (int k = 0; k < n; k++) {
            cout << "----";
        }
        cout << "-\n\t\t\t\t";
        for (j = 0; j < n; j++) {
            if (a[i][j] == 0) cout << "|   ";
            else
                cout << "| " << a[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << "\t\t\t\t";
    for (int k = 0; k < n; k++) {
        cout << "----";
    }
    cout << "-\n";
}

int check(int tmp[][10], int a[][10], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (tmp[i][j] != a[i][j])
                return 0;
    return 1;
}

bool checkover(int a[][10], int n) {
    int fl = 0, gl = 0, i, j;

    // Kiểm tra nếu có phần tử nào bằng 0
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (a[i][j] == 0) {
                fl = 1;
                break;
            }
        }
        if (fl) break; // Dừng lại nếu đã tìm thấy phần tử bằng 0
    }

    // Kiểm tra nếu có cặp phần tử liên tiếp nào bằng nhau theo hàng hoặc cột
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i < n - 1 && a[i + 1][j] == a[i][j]) {
                gl = 1;
                break;
            }
            if (j < n - 1 && a[i][j + 1] == a[i][j]) {
                gl = 1;
                break;
            }
        }
        if (gl) break; // Dừng lại nếu đã tìm thấy cặp phần tử liên tiếp bằng nhau
    }

    if (fl || gl) return true;
    else return false;
}

