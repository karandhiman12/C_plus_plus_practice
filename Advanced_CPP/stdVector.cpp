#include <iostream>
#include <string>
#include <vector>

struct Vertex {
    float x, y, z;
};

std::ostream& operator<<(std::ostream stream, const Vertex& vertex) {
    stream<<vertex.x<<", "<<vertex.y<<", "<<vertex.z<<std::endl;
    return stream;
}

int main() {
    //Vertex vertices[5];
    //Vertex* vertices = new Vertex[5];
    std::vector<Vertex> vertices;
    

    return 0;
}