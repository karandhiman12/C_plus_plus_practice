#include <iostream>
#include <string>
#include <vector>

// Define a struct to represent a 3D vertex
struct Vertex {
    float x, y, z;
};

// Overload the << operator to print Vertex objects
std::ostream& operator<<(std::ostream& stream, const Vertex& vertex) { // Pass stream by reference
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z << std::endl;
    return stream;
}

int main() {
    // Using std::vector to store Vertex objects dynamically
    std::vector<Vertex> vertices;
    vertices.push_back({1, 2, 3});
    vertices.push_back({4, 5, 6});

    // Print all vertices using a loop
    for (size_t i = 0; i < vertices.size(); i++) {
        std::cout << vertices[i] << " ";
    }
    std::cout << std::endl;

    //vertices.clear();
    // Remove the second element safely
    
    if (vertices.size() > 1) { // Ensure valid index before erasing
        vertices.erase(vertices.begin() + 1);
    }

    // Print remaining vertices using a range-based loop
    for (const auto& v : vertices) { // Use 'const auto&' for efficiency
        std::cout << v;
    }

    return 0;
}
