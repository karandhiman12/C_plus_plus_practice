#include <iostream>

int main() {
    int num;          // Integer: Used to store whole numbers. Typically 4 bytes (size may vary by system).
    float fNum;       // Float: Used to store single-precision floating-point numbers (decimal values). Typically 4 bytes.
    double dNum;      // Double: Used to store double-precision floating-point numbers (more precise decimal values). Typically 8 bytes.
    char character;   // Character: Used to store a single character. Typically 1 byte.
    bool flag;        // Boolean: Used to store true or false values. Typically 1 byte.
    long justInt;     // Long: Used to store larger whole numbers. At least 4 bytes (size may vary by system).
    long long bigInt; // Long Long: Used to store even larger whole numbers. At least 8 bytes.
    short smallInt;   // Short: Used to store smaller whole numbers. Typically 2 bytes.
    std::cout<<sizeof(long)<<std::endl;
    return 0;
}
