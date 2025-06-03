#include <iostream>
#include <string.h>

class String {
private:
    char* m_Buffer;   // Pointer to store the dynamically allocated character array
    unsigned int m_Size; // Stores the size of the string
public:
    // Constructor to initialize a String object with a given C-style string
    String(const char* string) {
        m_Size = strlen(string); // Compute string length
        m_Buffer = new char[m_Size + 1]; // Allocate memory for string and null terminator
        memcpy(m_Buffer, string, m_Size+1); // Copy string contents including '\0'
    } 

    // Destructor to free allocated memory
    ~String() { delete[] m_Buffer; }

    // Copy constructor to create a new String object as a copy of another
    String(const String& other) : m_Size(other.m_Size) {
        std::cout<<"Copied.."<<std::endl; // Indicate when a copy occurs
        m_Buffer = new char[m_Size + 1]; // Allocate new memory for the copied data
        memcpy(m_Buffer, other.m_Buffer, m_Size+1); // Copy contents from the original
    }

    // Overloading the stream operator to allow printing String objects
    friend std::ostream& operator<<(std::ostream& stream, const String& string);

    // Overloading the indexing operator for easy character access/modification
    char& operator[] (unsigned int index) {
        return m_Buffer[index];
    }
};

// Implementation of the overloaded stream operator for printing the string
std::ostream& operator<<(std::ostream& stream, const String& string) {
    stream<<string.m_Buffer; // Output stored character buffer
    return stream;
}

// Function to print a String object using the overloaded operator
void PrintString(const String& string) {
    std::cout<<string<<std::endl;
}

int main() {
    String string = "Cherno"; // Creating a String object initialized with "Cherno"
    String second = string; // Copy constructor is invoked here
    second[2] = 'a'; // Modifying the copied string

    // Printing both original and modified String objects
    //std::cout<<string<<std::endl;
    PrintString(string);
    PrintString(second);

    return 0;
}
