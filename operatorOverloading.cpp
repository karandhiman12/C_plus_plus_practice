#include <iostream>

// Structure to represent a 2D vector
struct Vector2 {
    float x, y;  // Member variables to store coordinates

    // Constructor to initialize a Vector2 object
    Vector2(float x, float y) 
        : x(x), y(y) {}

    // Function to add two Vector2 objects
    Vector2 Add(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y); // Returns the sum of two vectors
        // Alternative implementation: return *this + other;
    }

    // Overloaded '+' operator to enable vector addition using "+"
    Vector2 operator+(const Vector2& other) const {
        return Add(other); // Calls the Add function
        // Alternative implementation: return Vector2(x + other.x, y + other.y);
    }

    // Function to multiply two Vector2 objects
    Vector2 Multiply(const Vector2& other) const {
        return Vector2(x * other.x, y * other.y); // Returns the product of two vectors
        // Alternative implementation: return *this * other;
    }

    // Overloaded '*' operator to enable vector multiplication using "*"
    Vector2 operator*(const Vector2& other) const {
        return Multiply(other); // Calls the Multiply function
        // Alternative implementation: return Vector2(x * other.x, y * other.y);
    }

    // Overloaded '==' operator to compare two Vector2 objects for equality
    bool operator==(const Vector2& other) const {
        return (x == other.x && y == other.y); // Returns true if both coordinates match
    }
};

// Overloaded '<<' operator to print Vector2 objects using std::cout
std::ostream& operator<<(std::ostream& stream, const Vector2& other) {
    stream << other.x << ", " << other.y; // Prints the vector components
    return stream;
}

int main() {
    // Initializing three Vector2 objects
    Vector2 position(4.0f, 4.0f);  // Position vector
    Vector2 speed(0.5f, 1.5f);     // Speed vector
    Vector2 powerup(1.1f, 1.1f);   // Power-up modifier vector

    // Using the defined methods and operators to perform calculations
    Vector2 result1 = position.Add(speed.Multiply(powerup)); // Addition using function calls
    Vector2 result2 = position + (speed * powerup); // Addition using overloaded operators

    // Displaying the results
    std::cout << result1 << std::endl; // Prints first calculated vector
    std::cout << result2 << std::endl; // Prints second calculated vector

    // Comparing two results for equality
    std::cout << std::boolalpha << (result1 == result2) << std::endl; // Prints "true" or "false"

    return 0;
}
