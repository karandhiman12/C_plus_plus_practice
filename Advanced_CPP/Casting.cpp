#include <iostream>
#include <memory>

// Base and derived classes for demonstrating casting
class Animal {
public:
    virtual void speak() { std::cout << "Animal makes a sound\n"; }
    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() override { std::cout << "Woof!\n"; }
    void wagTail() { std::cout << "Dog wags tail\n"; }
};

class Cat : public Animal {
public:
    void speak() override { std::cout << "Meow!\n"; }
    void purr() { std::cout << "Cat purrs\n"; }
};

int main() {
    std::cout << "=== C++ CASTING DEMONSTRATION ===\n\n";

    // 1. IMPLICIT CASTING (Automatic conversions)
    std::cout << "1. IMPLICIT CASTING:\n";
    std::cout << "Automatic type conversions performed by compiler\n";
    
    int intValue = 42;
    double doubleValue = intValue;  // int to double (widening)
    std::cout << "int " << intValue << " -> double " << doubleValue << "\n";
    
    double pi = 3.14159;
    int truncatedPi = pi;  // double to int (narrowing, precision loss)
    std::cout << "double " << pi << " -> int " << truncatedPi << " (precision lost)\n\n";

    // 2. EXPLICIT C-STYLE CASTING
    std::cout << "2. C-STYLE CASTING (type)value:\n";
    std::cout << "Old C-style casting - powerful but dangerous\n";
    
    double value = 65.7;
    char charFromDouble = (char)value;  // Force conversion
    std::cout << "double " << value << " -> char '" << charFromDouble << "' (ASCII)\n";
    
    // Dangerous example - casting away constness
    const int constInt = 100;
    int* modifiablePtr = (int*)&constInt;  // Removes const (undefined behavior if modified)
    std::cout << "const int address cast to int* (dangerous!)\n\n";

    // 3. STATIC_CAST - Compile-time type conversion
    std::cout << "3. STATIC_CAST:\n";
    std::cout << "Safe compile-time conversions between related types\n";
    
    // Numeric conversions
    double d = 3.14159;
    int i = static_cast<int>(d);
    std::cout << "static_cast<int>(" << d << ") = " << i << "\n";
    
    // Pointer conversions in inheritance hierarchy
    Dog* dog = new Dog();
    Animal* animalPtr = static_cast<Animal*>(dog);  // Upcast (safe)
    animalPtr->speak();
    
    // Downcast (only safe if you're sure of the type)
    Animal* anotherAnimal = new Dog();
    Dog* dogPtr = static_cast<Dog*>(anotherAnimal);  // Downcast (risky without checking)
    dogPtr->wagTail();
    
    delete dog;
    delete anotherAnimal;
    std::cout << "\n";

    // 4. DYNAMIC_CAST - Runtime type checking
    std::cout << "4. DYNAMIC_CAST:\n";
    std::cout << "Safe runtime casting with type checking (requires virtual functions)\n";
    
    Animal* animals[] = { new Dog(), new Cat(), new Dog() };
    
    for (int idx = 0; idx < 3; ++idx) {
        std::cout << "Animal[" << idx << "]: ";
        animals[idx]->speak();
        
        // Try to cast to Dog
        Dog* d = dynamic_cast<Dog*>(animals[idx]);
        if (d) {
            std::cout << "  -> Successfully cast to Dog: ";
            d->wagTail();
        } else {
            std::cout << "  -> Not a Dog\n";
        }
        
        // Try to cast to Cat
        Cat* c = dynamic_cast<Cat*>(animals[idx]);
        if (c) {
            std::cout << "  -> Successfully cast to Cat: ";
            c->purr();
        } else {
            std::cout << "  -> Not a Cat\n";
        }
    }
    
    // Cleanup
    for (auto* animal : animals) {
        delete animal;
    }
    std::cout << "\n";

    // 5. CONST_CAST - Modify const/volatile qualifiers
    std::cout << "5. CONST_CAST:\n";
    std::cout << "Add or remove const/volatile qualifiers\n";
    
    const int constValue = 42;
    const int* constPtr = &constValue;
    
    // Remove const (be very careful - modifying original const data is undefined behavior)
    int* nonConstPtr = const_cast<int*>(constPtr);
    std::cout << "Removed const from pointer (value: " << *nonConstPtr << ")\n";
    
    // Adding const
    int normalInt = 123;
    int* normalPtr = &normalInt;
    const int* constifiedPtr = const_cast<const int*>(normalPtr);
    std::cout << "Added const to pointer (value: " << *constifiedPtr << ")\n\n";

    // 6. REINTERPRET_CAST - Low-level bit reinterpretation
    std::cout << "6. REINTERPRET_CAST:\n";
    std::cout << "Low-level casting - reinterprets bit patterns (very dangerous!)\n";
    
    int number = 1234567890;
    char* bytePtr = reinterpret_cast<char*>(&number);
    std::cout << "int " << number << " reinterpreted as bytes: ";
    for (size_t j = 0; j < sizeof(int); ++j) {
        std::cout << static_cast<int>(bytePtr[j]) << " ";
    }
    std::cout << "\n";
    
    // Pointer to integer conversion
    int* ptr = &number;
    uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
    std::cout << "Pointer " << ptr << " as integer: " << address << "\n\n";

    // 7. BEST PRACTICES SUMMARY
    std::cout << "=== BEST PRACTICES ===\n";
    std::cout << "1. Prefer static_cast for most conversions\n";
    std::cout << "2. Use dynamic_cast for safe downcasting with polymorphic types\n";
    std::cout << "3. Only use const_cast when absolutely necessary\n";
    std::cout << "4. Avoid reinterpret_cast unless doing low-level programming\n";
    std::cout << "5. Avoid C-style casts - they're too permissive\n";
    std::cout << "6. Let implicit casting handle simple conversions when safe\n";

    return 0;
}