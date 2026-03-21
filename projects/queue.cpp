#include <iostream>
#include "../node.h"

class QueueArray {
public:
    QueueArray(int cap, int size):
        cap{cap}, head{0}, tail{0}, size{0} {
        array = new int[cap];
    }

    ~QueueArray() {
        delete [] array;
    }

    int push(int data) {
        if (tail + 1 >= cap) return 1;
        array[tail] = data;
        tail = (tail + 1) % cap;
        size++;
        return 0;
    }

    int pop(int *dest = nullptr) {
        if (tail == -1) return 1;
        if (dest) *dest = array[head];
        head = (head + 1) % cap;
        size--;
        return 0;
    }

    void show() {
        if (size == 0) {
            std::cout << "Empty\n";
            return;
        }

        for (int i = 0; i < size; i++) {
            int index = (head + i) % cap;
            cout << array[index] << ' ';
        }
        cout << '\n';
    }

private:
    int* array;
    int cap, size, tail, head;
};


class QueueList {
public:
    QueueList(): cnt{0} {
        head = tail = nullptr;
    }

    ~QueueList() {
        while (head != nullptr) {
            this->pop();
        }
    }

    void push(node *nd) {
        if (tail == nullptr) head = nd;
        else tail->next = nd;
        tail = nd;
        cnt++;
    }

    node* pop() {
        if (head == nullptr) return head;
        node *tmp = head;
        head = head->next;
        cnt--;
        return tmp;
    }

    void show() {
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

private:
    node *head, *tail;
    int cnt;
};

int main() {
    int N;
    cout << "Speed test for inserting and deleting elements in a queue\n";
    cout << "Enter the number of elements: ";
    cin >> N;

    QueueArray qa(N);
    QueueList ql;

    cout << "Time to insert " << N << " elements for an array-based queue: " << array_timing_push(N, qa) << '\n';
    cout << "Time to insert " << N << " elements for an list-based queue: " << list_timing_push(N, ql) << '\n';

    cout << "Time to delete " << N << " elements for an array-based queue: " << array_timing_pop(N, qa) << '\n';
    cout << "Time to delete " << N << " elements for an list-based queue: " << list_timing_pop(N, ql) << '\n';

    getchar();
}
