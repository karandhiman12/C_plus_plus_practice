#include <iostream>

class Example {
public:
    int value;

    // Constructor
    Example(int v) : value(v) {
        std::cout << "Constructor called for value: " << value << std::endl;
    }

    // Destructor
    ~Example() {
        std::cout << "Destructor called for value: " << value << std::endl;
    }
};

void stackLifetime() {
    // Object created on stack
    Example obj(10); 

    // The destructor for 'obj' will be called automatically when the function ends
}

void heapLifetime() {
    // Object created on heap
    Example* obj = new Example(20);

    // Destructor will NOT be called automatically; we need to delete the object explicitly
    delete obj;
}

int main() {
    std::cout << "Entering stackLifetime function...\n";
    stackLifetime();  // Object created and destroyed within function scope

    std::cout << "Entering heapLifetime function...\n";
    heapLifetime();   // Object created and must be manually deleted

    std::cout << "End of program.\n";

    return 0;
}
