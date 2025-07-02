#include <iostream>

// A simple 2D vector structure
struct Vector2 {
    float x, y;
};

// A 4D vector structure using unions and anonymous structs
// It allows accessing the same memory as either four floats (x, y, z, w)
// or as two Vector2 structures (a and b)
struct Vector4 {
    union {
        struct {
            float x, y, z, w;  // Standard 4D representation
        }; 
        struct {
            Vector2 a, b;      // Interpreted as two 2D vectors
        };    
    };
};

// Function to print a Vector2's components
void PrintVector2(const Vector2& vector) {
    std::cout << vector.x << ", " << vector.y << "\n";
}

int main() {
    // Define a structure containing a union of float and int
    struct UnionStruct {
        union {
            float a;
            int b;
        };
    };
    
    UnionStruct u;
    u.a = 2.0f;  // Set the float field
    std::cout << u.a << ", " << u.b << "\n";  // Print float and reinterpret as int (type punning)
    std::cout << "-----------------------\n";

    // Initialize Vector4 using its float representation
    Vector4 vector = {1.0f, 2.0f, 3.0f, 4.0f};

    // Print the first Vector2 (a = x, y) and second (b = z, w)
    PrintVector2(vector.a);
    PrintVector2(vector.b);

    // Modify w component directly
    vector.w = 500.f;
    std::cout << "-----------------------\n";

    // Re-print a and b to show updated values due to shared memory
    PrintVector2(vector.a);
    PrintVector2(vector.b);
    std::cout << "-----------------------\n";
    
    return 0;
}
