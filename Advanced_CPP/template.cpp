#include <iostream>
#include <string>

template<typename T>
void Print(T value) {
    std::cout<<value<<std::endl;
}

template<typename T, int N>
class Array {
private:
    T m_array[N];
public:
    int GetSize() const {
        return N;
    }
};

int main() {
    Print(4);
    Print(45.667);
    Print("String");

    Array<std::string, 45> arr;
    std::cout<<arr.GetSize()<<std::endl;

    return 0;
}