#include <iostream>

int main() {
    // Declare a constant integer variable
    const int MAX_AGE = 90;

    // Allocate dynamic memory for an integer
    int *a = new int;

    // Assign 'a' the address of MAX_AGE by bypassing the const restriction
    // WARNING: This is unsafe and can lead to undefined behavior
    a = (int*)&MAX_AGE; // By passing const promise

    // Output the value stored at 'a' (which is MAX_AGE)
    std::cout << *a << std::endl;

    // Different types of pointers

    // Pointer to a constant integer (cannot modify the value)
    const int* a = new int;

    // Constant pointer to an integer (cannot modify the pointer itself)
    int* const b = new int;

    // Constant pointer to a constant integer (neither value nor pointer can be modified)
    const int* const c = new int;

    return 0; // Return 0 to indicate successful execution
}
