#include "../test.h"
#include "stack.h"

using std::cout;
using std::cin;

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


