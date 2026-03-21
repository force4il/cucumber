#include <iostream>
#include "test.h"
#include "node.h"

using std::cout;
using std::cin;

class StackArray {
public:
    StackArray(int cap = 1): cap{cap}, tail{-1} {
    	array = new int[cap];
	}

    ~StackArray() {
    	delete [] array;
	}

    int push(int data) {
    	if (tail + 1 >= cap) return 1;
    	array[++tail] = data;
    	return 0;
	}

	int pop(int *dest = nullptr) {
    	if (tail == -1) return 1;
    	if (dest) *dest = array[tail];
    	tail--;
    	return 0;
	}

	void show() {
    	if (tail == -1) std::cout << "Empty";
   		for (int i = 0; i <= tail; i++)
        	cout << array[i] << ' ';
    	cout << '\n';
	}

private:
    int* array;
    int cap, tail;
};

class StackList {
public:
    StackList(): head{nullptr}, cnt{0} {}

	~StackList() {
    	node *cur;
    	while (cur = pop()) {
			delete cur;
		}
	}

	void push(node *nd) {
    	nd->next = head;
   	 head = nd;
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
        	cout << cur.data << ' ';
        	if (cur.next != nullptr) cur = *cur.next;
    	}
    	cout << '\n';
	}

private:
    node* head;
    int cnt;
};

int main() {
    int N;
    cout << "Speed test for inserting and deleting elements in a stack\n";
    cout << "Enter the number of elements: ";
    cin >> N;

    StackArray sa(N);
    StackList sl;

    cout << "Time to insert " << N << " elements for an array-based stack: " << array_timing_push(N, sa) << '\n';
    cout << "Time to insert " << N << " elements for an list-based stack: " << list_timing_push(N, sl) << '\n';

    cout << "Time to delete " << N << " elements for an array-based stack: " << array_timing_pop(N, sa) << '\n';
    cout << "Time to delete " << N << " elements for an list-based stack: " << list_timing_pop(N, sl) << '\n';
}
