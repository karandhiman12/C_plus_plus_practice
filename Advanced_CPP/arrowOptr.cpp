#include <iostream>
#include <memory>

class Entity {
public:
    void Print() const {
        std::cout<<"THE OBJECT..."<<std::endl;  // Outputs a message when called.
    }
    int x;  // Public member variable.
};

// Custom smart pointer 'ScopedPtr' that manages the lifetime of an 'Entity' object.
class ScopedPtr {
private:
    Entity* m_Obj;  // Raw pointer to an 'Entity' object.
public:
    // Constructor: takes an Entity pointer and stores it.
    ScopedPtr(Entity* entity) : m_Obj(entity) { }

    // Destructor: ensures proper cleanup to prevent memory leaks.
    ~ScopedPtr() { delete m_Obj; }

    // Overloaded '->' operator for direct access to the Entity's members and methods.
    Entity* operator->() {
        return m_Obj;
    }

    // Const version of '->' operator to allow usage with const objects.
    const Entity* operator->() const {
        return m_Obj;
    }
};

// A simple struct representing a 3D vector with three floating-point coordinates.
struct Vector3 {
    float x, y, z;
};

int main() {
    Entity e;  // Creates an instance of 'Entity' on the stack.
    e.Print(); // Calls 'Print' on the instance.

    Entity* ptr = &e; // Creates a pointer to the stack-allocated 'Entity'.
    //(*ptr).Print(); // Alternative way to call 'Print' using dereferencing (commented out).
    ptr->Print();  // Calls 'Print' through the pointer.
    ptr->x = 45;   // Modifies the 'x' member variable of 'Entity'.

    ScopedPtr e6 = new Entity();  // Creates a 'ScopedPtr' managing a dynamically allocated 'Entity'.
    e6->Print();  // Calls 'Print' using the smart pointer.

    const ScopedPtr e7(new Entity());  // Creates a const ScopedPtr managing a dynamically allocated Entity.
    //const ScopedPtr e7 = new Entity();  // Alternative way to initialize 'e7' (commented out).
    e7->Print();  // Calls 'Print' through the smart pointer.

    // Calculates the memory offset of 'x' inside 'Vector3' using a null pointer.
    int offset = (int)&((Vector3*)nullptr)->x;

    return 0; // Indicates successful execution.
}
