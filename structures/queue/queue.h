#pragma once
#include <iostream>
#include "../node.h"

class QueueArray {
public:
    QueueArray(int cap = 0, int size = 0);
    ~QueueArray();

    int push(int data);
    int pop(int* dest = nullptr);
    void show();

private:
    int* array;
    int cap, size, tail, head;
};

class QueueList {
public:
    QueueList();
    ~QueueList();

    void push(node* nd);
    node* pop();
    void show();

private:
    node *head, *tail;
    int cnt;
};
