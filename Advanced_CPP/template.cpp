#include <iostream>
#include <string>

// Template function to print any type of value
template<typename T>
void Print(T value) {
    std::cout << value << std::endl;
}

// Template class for a fixed-size array
template<typename T, int N>
class Array {
private:
    T m_array[N]; // Internal array of type T with size N
public:
    // Function to return the size of the array
    int GetSize() const {
        return N;
    }
};

int main() {
    // Demonstrating the Print function with different data types
    Print(4);          // Prints an integer
    Print(45.667);     // Prints a floating-point number
    Print("String");   // Prints a string

    // Creating an Array object with std::string type and size 45
    Array<std::string, 45> arr;
    std::cout << arr.GetSize() << std::endl; // Prints the size of the array

    return 0;
}
