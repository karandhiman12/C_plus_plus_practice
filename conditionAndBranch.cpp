#include <iostream>

int main() {
    int x = 5;
    //bool compareResult = x == 6;

    if(x == 5) {
        std::cout<<"Hello world!"<<std::endl;
    }
    const char *ptr = nullptr;

    if(ptr)
        std::cout<<ptr;
    else if(ptr == "Hello")
        std::cout<<"Ptr is Hello!";
    else
        std::cout<<"Ptr is null!";
        
    return 0;
}