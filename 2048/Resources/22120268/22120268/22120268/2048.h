#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

void upmove(int a[][10], int n, int& score);
void downmove(int a[][10], int n, int& score);
void leftmove(int a[][10], int n, int& score);
void rightmove(int a[][10], int n, int& score);
void addblock(int a[][10], int n);
void disp(const int a[][10], int n, int score);
int check(int tmp[][10], int a[][10], int n);
bool checkover(int a[][10], int n);
