#include <iostream> // Includes the input-output stream library

// A function is a block of code that performs a specific task. It usually takes some input, processes it, and returns an output. Functions help organize code into manageable sections and enable code reuse.

// Function that multiplies two integers and returns the result
int Multiply(int a, int b) {
    return a * b; // Returns the product of a and b
}

// Function that multiplies two integers and logs the result
void MultiplyAndLog(int x, int y) {
    int result = Multiply(x, y); // Calls the Multiply function and stores the result
    std::cout << result << std::endl; // Prints the result to the console
}

int main() {
    MultiplyAndLog(4, 5); // Calls MultiplyAndLog with arguments 4 and 5
    MultiplyAndLog(56, 45); // Calls MultiplyAndLog with arguments 56 and 45
    MultiplyAndLog(45, 33); // Calls MultiplyAndLog with arguments 45 and 33
}
