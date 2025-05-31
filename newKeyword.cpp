#include <iostream>

using namespace std;

int main() {
    // Using 'new' to allocate memory dynamically
    int* ptr = new int;  // Allocating an integer dynamically

    // Assigning value to dynamically allocated memory
    *ptr = 42;

    // Displaying the value stored in the allocated memory
    cout << "Value at dynamically allocated memory: " << *ptr << endl;

    // Freeing up the allocated memory using 'delete'
    delete ptr;

    // Setting pointer to nullptr after deletion (good practice)
    ptr = nullptr;

    return 0;
}
