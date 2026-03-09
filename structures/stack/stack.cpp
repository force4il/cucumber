#include "stack.h"

StackArray::StackArray(int cap) : cap{cap}, tail{-1} {
    array = new int[cap];
}

StackArray::~StackArray() {
    delete [] array;
}

int StackArray::push(int data) {
    if (tail + 1 >= cap) return 1;
    array[++tail] = data;
    return 0;
}

int StackArray::pop(int *dest) {
    if (tail == -1) return 1;
    if (dest) *dest = array[tail];
    tail--;
    return 0;
}

void StackArray::show() {
    if (tail == -1) std::cout << "Empty";
    for (int i = 0; i <= tail; i++)
        std::cout << array[i] << ' ';
    std::cout << '\n';
}


StackList::StackList() : head{nullptr}, cnt{0} {}

StackList::~StackList() {
    node *cur;
    while (cur = pop()) { delete cur; }
}

void StackList::push(node *nd) {
    nd->next = head;
    head = nd;
    cnt++;
}

node *StackList::pop() {
    if (head == nullptr) return head;
    node *tmp = head;
    head = head->next;
    cnt--;
    return tmp;
}

void StackList::show() {
    if (head == nullptr) {
        std::cout << "Empty";
        return;
    }
    node cur = *head;
    int i = 0;
    while (i++ != cnt) {
        std::cout << cur.data << ' ';
        if (cur.next != nullptr) cur = *cur.next;
    }
    std::cout << '\n';
}
