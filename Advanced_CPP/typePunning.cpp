#include <iostream>

// Define a struct with two integer members
struct Entity
{
    int x, y;

    // Return a pointer to the first member (x)
    int* GetPositions() 
    {
        return &x;
    }
};

int main() {
    int a = 56;

    // Reinterpret the bits of integer 'a' as a float
    float value = *(float*)&a; 
    std::cout << value << "\n"; // Outputs a float representation of 56's binary pattern

    // Create an Entity instance with x = 5, y = 8
    Entity e = {5, 8};

    // Treat the address of 'e' as an int pointer — accessing raw memory directly
    int* position0 = (int*)&e;

    // Cast the address of 'e' to a char* (for byte-wise pointer arithmetic)
    // Then add 4 to skip 'x' (4 bytes), and cast back to int* to access 'y'
    int y = *(int*)((char*)&e + 4);

    // Get pointer to the x member via GetPositions()
    int* position = e.GetPositions();

    // Modify x via position[0] — position[1] points to y!
    position[0] = 999;

    // Print both x and y via position pointer — x was changed to 999
    std::cout << position[0] << ", " << position[1] << "\n"; 

    // Print y again using raw byte-wise offset
    std::cout << "Y: " << y << "\n";   

    return 0;
}
