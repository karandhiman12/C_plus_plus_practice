#include <stdio.h>

// Method 1: Simple iteration - check each bit
int countSetBits_v1(int n) {
    int count = 0;
    while (n) {
        count += n & 1;  // Check if last bit is 1
        n >>= 1;         // Right shift to check next bit
    }
    return count;
}

// Method 2: Brian Kernighan's Algorithm (most efficient)
// n & (n-1) removes the rightmost set bit
int countSetBits_v2(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);  // Remove rightmost set bit
        count++;
    }
    return count;
}

// Method 3: Lookup table method (fastest for repeated calls)
int countSetBits_v3(int n) {
    // Precomputed lookup table for 8 bits (0-255)
    int table[256];
    table[0] = 0;
    for (int i = 1; i < 256; i++) {
        table[i] = table[i >> 1] + (i & 1);
    }
    
    int count = 0;
    count += table[n & 0xff];           // First 8 bits
    count += table[(n >> 8) & 0xff];    // Next 8 bits
    count += table[(n >> 16) & 0xff];   // Next 8 bits
    count += table[(n >> 24) & 0xff];   // Last 8 bits
    return count;
}

// Function to print binary representation
void printBinary(int n) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
}

int main() {
    int testNumbers[] = {0, 5, 7, 15, 255, 1023, -1};
    int size = sizeof(testNumbers) / sizeof(testNumbers[0]);
    
    printf("Counting set bits in integers:\n\n");
    printf("%-10s %-35s %-10s\n", "Number", "Binary", "Set Bits");
    printf("--------------------------------------------------------\n");
    
    for (int i = 0; i < size; i++) {
        int num = testNumbers[i];
        printf("%-10d ", num);
        printBinary(num);
        printf(" %-10d\n", countSetBits_v2(num));
    }
    
    printf("\n========================================================\n");
    printf("\nExample walkthrough for number 13:\n");
    printf("Binary: ");
    printBinary(13);
    printf("\n\nBrian Kernighan's Algorithm steps:\n");
    
    int n = 13;
    int step = 1;
    while (n) {
        printf("Step %d: n = ", step);
        printBinary(n);
        printf(" (%d)\n", n);
        n &= (n - 1);
        printf("        n & (n-1) = ");
        printBinary(n);
        printf(" (%d)\n\n", n);
        step++;
    }
    
    printf("Total set bits: %d\n", countSetBits_v2(13));
    
    return 0;
}