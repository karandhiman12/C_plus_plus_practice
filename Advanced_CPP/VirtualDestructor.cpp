#include <iostream>

// Base class with constructor and virtual destructor
class Base {
public:
    Base() { std::cout << "Base Constructor\n"; }              // Prints when Base object is created
    virtual ~Base() { std::cout << "Base Destructor\n"; }      // Virtual to allow proper cleanup when derived classes are deleted via base pointer
};

// Derived class inheriting from Base
class Derived : public Base {
public:
    Derived() { std::cout << "Derived Constructor\n"; }        // Prints when Derived object is created
    ~Derived() { std::cout << "Derived Destructor\n"; }        // Prints when Derived object is destroyed
};

int main() {
    std::cout << "---------------\n";

    // Create and delete a Base object using a Base pointer
    Base* base = new Base();     // Only Base constructor and destructor will be called
    delete base;                 // Base destructor is invoked

    std::cout << "---------------\n";

    // Create and delete a Derived object using a Derived pointer
    Derived* derived = new Derived();  // Both Base and Derived constructors are called
    delete derived;                    // Derived destructor followed by Base destructor

    std::cout << "---------------\n";

    // Demonstrate polymorphism: create a Derived object via a Base pointer
    Base* poly = new Derived();  // Base constructor then Derived constructor
    delete poly;                 // Derived destructor then Base destructor (correct order due to virtual destructor)

    return 0;
}
