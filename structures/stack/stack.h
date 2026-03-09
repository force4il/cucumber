#pragma once
#include <iostream>
#include "../node.h"

class StackArray {
public:
    StackArray(int cap = 1);
    ~StackArray();

    int push(int data);
    int pop(int* dest = nullptr);
    void show();

private:
    int* array;
    int cap, tail;
};

class StackList {
public:
    StackList();
    ~StackList();

    void push(node* nd);
    node* pop();
    void show();

private:
    node* head;
    int cnt;
};
