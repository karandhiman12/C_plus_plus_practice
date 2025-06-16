#include <iostream>

// Defining a namespace named "FirstNamespace"
namespace FirstNamespace {
    void display() {
        std::cout << "Inside FirstNamespace" << std::endl;
    }
}

// Defining another namespace named "SecondNamespace"
namespace SecondNamespace {
    void display() {
        std::cout << "Inside SecondNamespace" << std::endl;
    }
}

int main() {
    // Calling function from FirstNamespace
    FirstNamespace::display();

    // Calling function from SecondNamespace
    SecondNamespace::display();

    // Using "using" directive to simplify access to FirstNamespace functions
    using namespace FirstNamespace;
    display(); // This refers to FirstNamespace::display()

    return 0;
}
