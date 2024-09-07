#pragma once
#include <stack>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>

struct GameState {
    int board[10][10];
    int score;
};

template<typename T>
class StackNode {
public:
    T data;
    StackNode<T>* next;

    StackNode(const T& data) : data(data), next(nullptr) {}
};

template<typename T>
class Stack {
private:
    StackNode<T>* topNode;

public:
    Stack() : topNode(nullptr) {}

    ~Stack() {
        while (!empty()) {
            pop();
        }
    }

    void push(const T& data) {
        StackNode<T>* newNode = new StackNode<T>(data);
        if (topNode == nullptr) {
            topNode = newNode;
        }
        else {
            newNode->next = topNode;
            topNode = newNode;
        }
    }

    void pop() {
        if (topNode == nullptr) {
            return;
        }
        StackNode<T>* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    T& top() const {
        if (topNode == nullptr) {
            throw "Stack is empty";
        }
        return topNode->data;
    }

    bool empty() const {
        return topNode == nullptr;
    }
};
