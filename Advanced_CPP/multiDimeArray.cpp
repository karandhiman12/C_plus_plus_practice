#include <iostream>

int main() {
    // Dynamically allocate a 2D array (5x5)
    int** a2d = new int*[5]; // Allocate memory for 5 rows (array of int pointers)

    for (int i = 0; i < 5; i++)
        a2d[i] = new int[5]; // Allocate memory for 5 columns in each row

    // Dynamically allocate a 3D array (5x5x5)
    int*** a3d = new int**[5]; // Allocate memory for 5 layers (array of pointer to pointer)

    for(int i = 0; i< 5; i++) {
        a3d[i] = new int*[5]; // For each layer, allocate 5 rows

        for(int j = 0; j< 5; j++) {
            a3d[i][j] = new int[5]; // For each row, allocate 5 columns
        }
    }

    // Deallocate the 2D array memory
    for(int i = 0; i < 5; i++)
        delete[] a2d[i]; // Delete each row
    delete[] a2d; // Delete the array of pointers

    // Note: Memory allocated for the 3D array is not deallocated here.
    // This will cause a memory leak if not handled properly.

    return 0;
}
