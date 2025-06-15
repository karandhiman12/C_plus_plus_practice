#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// Function that applies the given function `func` to each element in the vector `values`
void ForEach(const std::vector<int>& values, const std::function<void(int)>& func)
{
    for(int value: values)
        func(value); // Calls the provided function on each element
}

int main()
{
    // Initialize a vector with integer values
    std::vector<int> values = {1,5,4,2,3};

    // Use std::find_if to find the first element in `values` that is greater than 3
    auto it = std::find_if(values.begin(), values.end(), [](int value) { return value > 3; });

    // Output the found element
    std::cout<<"iterator it: "<<(*it)<<std::endl;

    int a = 56;

    // Example lambda with capture by value (`=`), but marked mutable so modifications are allowed
    // Without `mutable`, the lambda would be unable to modify `a`
    auto lambda = [=](int value) mutable { 
        a = 44; // Modifying the captured variable
        std::cout<<"Value: "<<a<<std::endl; 
    };

    // Call ForEach to execute `lambda` on each element in `values`
    ForEach(values, lambda);

    return 0;
}
