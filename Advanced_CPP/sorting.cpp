#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

int main() {
    // Initialize a vector with unsorted integers
    std::vector<int> values = {3, 5, 1, 4, 2};
    //std::sort(values.begin(), values.end(), std::greater<int>());
    // Custom sort using a lambda expression
    // The lambda treats the value '1' as the highest, placing it at the end
    std::sort(values.begin(), values.end(), [](int a, int b) {
        if (a == 1)
            return false; // If 'a' is 1, it should come after 'b'
        if (b == 1)
            return true;  // If 'b' is 1, 'a' should come before 'b'
        return a < b;     // Otherwise, sort in ascending order
    });

    // Print the sorted vector
    for (int value : values)
        std::cout << value << " "; // Output elements separated by space

    return 0;
}
