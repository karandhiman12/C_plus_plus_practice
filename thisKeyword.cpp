#include <iostream>

class Example {
private:
    int value;

public:
    // Constructor to initialize the value
    Example(int value) {
        // Using 'this' to differentiate between local and member variable
        this->value = value;
    }

    // Function to display the value
    void display() {
        // Using 'this' to access the member variable
        std::cout << "Value: " << this->value << std::endl;
    }

    // Returning current object using 'this'
    Example* getPointer() {
        return this;
    }
};

int main() {
    // Creating an object
    Example obj(42);
    
    // Displaying the value
    obj.display();

    // Using 'this' to return the current object
    Example* ptr = obj.getPointer();
    std::cout << "Address of object: " << ptr << std::endl;

    return 0;
}
