#include "queue.h"

QueueArray::QueueArray(int cap, int size):
cap{cap}, head{0}, tail{0}, size{0} {
    array = new int[cap];
}

QueueArray::~QueueArray() {
    delete [] array;
}

int QueueArray::push(int data) {
    if (tail + 1 >= cap) return 1;
    array[tail] = data;
    tail = (tail + 1) % cap;    
    size++;
    return 0;
}

int QueueArray::pop(int *dest) {
    if (tail == -1) return 1;
    if (dest) *dest = array[head];
    head = (head + 1) % cap;     
    size--;
    return 0;
}

void QueueArray::show() {
    if (size == 0) {
        std::cout << "Empty\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        int index = (head + i) % cap;  
        std::cout << array[index] << ' ';
    }
    std::cout << '\n';
}


QueueList::QueueList() : cnt{0} {
    head = tail = nullptr;
}

QueueList::~QueueList() {
    while (head != nullptr)
        this->pop();
}

void QueueList::push(node *nd) {
    if (tail == nullptr) head = nd;
    else tail->next = nd;
    tail = nd;
    cnt++;
}

node *QueueList::pop() {
    if (head == nullptr) return head;
    node *tmp = head;
    head = head->next;
    cnt--;
    return tmp;
}

void QueueList::show() {
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
