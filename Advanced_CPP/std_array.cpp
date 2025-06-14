#include <iostream>
#include <array>
#include <algorithm> // For std::sort

int main() {
    // Declare and initialize std::array of 5 integers
    std::array<int, 5> arr = {10, 20, 30, 40, 50};

    // Accessing elements using [] and at()
    std::cout << "First element (using []): " << arr[0] << std::endl;
    std::cout << "Second element (using at()): " << arr.at(1) << std::endl;

    // Size of the array
    std::cout << "Size of the array: " << arr.size() << std::endl;

    // Front and back elements
    std::cout << "Front element: " << arr.front() << std::endl;
    std::cout << "Back element: " << arr.back() << std::endl;

    // Iterating using range-based for loop
    std::cout << "Elements in array: ";
    for (int value : arr) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Sorting the array
    std::sort(arr.begin(), arr.end());

    std::cout << "Sorted array: ";
    for (int value : arr) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Filling array with a specific value
    arr.fill(100);
    std::cout << "Array after fill(100): ";
    for (int value : arr) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
