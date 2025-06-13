#include <iostream>
#include <vector>
#include <map>

int main() {
    // 1. Using auto for basic type deduction
    auto num = 10;       // num is deduced as int
    auto pi = 3.14159;   // pi is deduced as double
    auto ch = 'A';       // ch is deduced as char

    std::cout << "num: " << num << " (type: int)" << std::endl;
    std::cout << "pi: " << pi << " (type: double)" << std::endl;
    std::cout << "ch: " << ch << " (type: char)" << std::endl;

    // 2. Using auto with pointers
    int x = 42;
    auto ptr = &x;  // ptr is deduced as int*
    std::cout << "Pointer value: " << *ptr << " (type: int*)" << std::endl;

    // 3. Using auto with STL containers
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto it = vec.begin();  // it is deduced as std::vector<int>::iterator
    std::cout << "First element in vector: " << *it << std::endl;

    // 4. Using auto in range-based for loops
    std::cout << "Vector elements: ";
    for (auto val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // 5. Using auto with maps
    std::map<std::string, int> ageMap = {{"Alice", 25}, {"Bob", 30}};
    for (auto pair : ageMap) {
        std::cout << pair.first << " is " << pair.second << " years old." << std::endl;
    }

    // 6. Using auto with lambda functions
    auto add = [](int a, int b) { return a + b; };
    std::cout << "Sum using lambda: " << add(5, 3) << std::endl;

    return 0;
}
