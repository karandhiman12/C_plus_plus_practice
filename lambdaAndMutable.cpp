#include <iostream>

class Example {
private:
    mutable int count; // 'mutable' allows modification even in a const member function
public:
    Example() : count(0) {}

    void show() const { // 'const' means this function cannot modify member variables (except mutable ones)
        count++; // Allowed due to 'mutable' keyword
        std::cout << "Called show() " << count << " times.\n";
    }
};

int main() {
    Example obj;
    
    obj.show(); // First call
    obj.show(); // Second call
    
    // Demonstrating lambda functions
    int x = 10;
    
    // Capture 'x' by value and modify it inside the lambda (modification is local to the lambda)
    auto lambda1 = [x]() mutable {
        x += 5;
        std::cout << "Inside lambda1, x = " << x << std::endl;
    };

    lambda1();
    std::cout << "Outside lambda1, x = " << x << std::endl; // 'x' remains unchanged

    // Capture 'x' by reference and modify it inside the lambda (modifies original variable)
    auto lambda2 = [&x]() {
        x += 10;
        std::cout << "Inside lambda2, x = " << x << std::endl;
    };

    lambda2();
    std::cout << "Outside lambda2, x = " << x << std::endl; // 'x' is now modified
    std::cout<<"The end"<<std::endl;
    return 0;
}
