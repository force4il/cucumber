#pragma once 

struct node {
    node(int data): data{data}, next{nullptr} {}
    int data;
    node* next;
};
