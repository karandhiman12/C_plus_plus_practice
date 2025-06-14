#include <iostream>
#include <vector>

// Function to print an integer value
void PrintValue(int value)
{
    std::cout<<"Value: "<<value<<std::endl;
}

// Function that takes a vector of integers and applies a function to each element
void ForEach(const std::vector<int>& values, void(*func)(int))
{
    for(int value: values)
        func(value); // Calls the provided function on each element
}

// Function that prints "Hello world" along with an integer value
void HelloWorld(int a)
{
    std::cout<<"Hello world, with value: "<<a<<std::endl;
}

int main()
{
    // Defining function pointer using `auto`
    auto Function = HelloWorld; // Equivalent to &HelloWorld

    // Explicit function pointer declaration
    void(*karan)(int) = HelloWorld;

    // Typedef for function pointer
    typedef void(*cherno)(int);
    cherno ye = HelloWorld;

    // Calling HelloWorld using different function pointers
    ye(5);
    karan(5);
    HelloWorld(8);

    // Creating a vector with some integer values
    std::vector<int> values = {1,5,4,2,3};

    // Applying PrintValue function to each element in values
    ForEach(values, PrintValue);

    // Using a lambda function to print values in a different format
    ForEach(values, [](int value) { std::cout<<"Value: "<<value<<", "; });

    return 0;
}
