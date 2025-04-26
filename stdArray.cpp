#include <iostream>
#include <array> // Include the header for std::array

int main() {
    // Declare and initialize an std::array
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    // Access and print elements of the array using a range-based loop
    std::cout << "Elements of the array:" << std::endl;
    for (int elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Access elements using indexing
    std::cout << "First element: " << arr[0] << std::endl;

    // Access elements safely using the .at() method
    std::cout << "Second element: " << arr.at(1) << std::endl;

    // Print the size of the array
    std::cout << "Size of the array: " << arr.size() << std::endl;

    // Modify an element
    arr[2] = 10;
    std::cout << "After modification: " << arr[2] << std::endl;

    // Check if the array is empty
    std::cout << "Is the array empty? " << (arr.empty() ? "Yes" : "No") << std::endl;

    return 0;
}
