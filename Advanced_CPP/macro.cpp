#include <iostream>

// Object-like macro: Defines a constant value
#define PI 3.14159

// Function-like macro: Computes the square of a number
#define SQUARE(x) ((x) * (x))

// Multi-line macro: Defines a function-like macro spanning multiple lines
#define PRINT_DETAILS(name, age) \
    std::cout << "Name: " << name << std::endl; \
    std::cout << "Age: " << age << std::endl;

// Token pasting macro: Combines two tokens into one
#define CONCAT(a, b) a##b

// Stringizing macro: Converts a macro argument into a string literal
#define TO_STRING(x) #x

// Conditional compilation: Enables debug mode if DEBUG is defined
#define DEBUG 1

int main() {
    // Using the object-like macro
    std::cout << "Value of PI: " << PI << std::endl;

    // Using the function-like macro
    int num = 5;
    std::cout << "Square of " << num << " is: " << SQUARE(num) << std::endl;

    // Using the multi-line macro
    PRINT_DETAILS("Alice", 25);

    // Using the token pasting macro
    int CONCAT(my, Var) = 10;  // Creates variable `myVar`
    std::cout << "Value of myVar: " << myVar << std::endl;

    // Using the stringizing macro
    std::cout << "Stringized version of PI: " << TO_STRING(PI) << std::endl;

    // Conditional compilation
    #ifdef DEBUG
        std::cout << "Debug mode is enabled!" << std::endl;
    #else
        std::cout << "Debug mode is disabled!" << std::endl;
    #endif

    // Undefining a macro
    #undef PI
    #ifdef PI
        std::cout << "PI is still defined!" << std::endl;
    #else
        std::cout << "PI has been undefined!" << std::endl;
    #endif

    return 0;
}
