#include "../test.h"

using std::cout;
using std::cin;

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

