#include <iostream>
#include <string>  // Include the string header for std::string operations

int main() {
    // Declare a C-style string (constant pointer to characters)
    const char* name = "Cherno";

    // Declare a character array (C-style string) with explicit size
    char name2[7] = {'c', 'h', 'e', 'r', 'n', 'o', '\0'};

    // Declare a C++ string object
    std::string name3 = "Cherno";

    // Concatenate two string literals using std::string for proper concatenation
    std::string name4 = "The" + std::string(" Cherno");

    // Append additional text to the string
    name4 += ": C++";

    // Check if the substring "no" exists in name4
    bool contains = name4.find("no") != std::string::npos;

    // Print the result (1 if found, 0 if not found)
    std::cout << contains << std::endl;

    // Declare different types of wide-character string literals
    const wchar_t* var = L"Cherno";      // Wide character string
    const char16_t* var2 = u"Cherno";    // UTF-16 encoded string
    const char32_t* var3 = U"Cherno";    // UTF-32 encoded string

    return 0;  // Return 0 to indicate successful execution
}
