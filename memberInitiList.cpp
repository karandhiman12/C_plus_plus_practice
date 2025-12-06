#include <iostream>

class Example {
public:
    // Default constructor: prints a message when an Example object is created
    Example() {
        std::cout << "CREATED ENTITY" << std::endl;
    }

    // Parameterized constructor: prints a message showing the passed integer value
    Example(int x) {
        std::cout << "CREATED ENTITY WITH: " << x << std::endl;
    }
};

class Entity {
private:
    std::string m_Name;  // Name of the entity
    int m_Score;         // Score associated with the entity
    Example m_Example;   // Example object as a member variable

public:
    // Default constructor: initializes member variables using an initializer list
    Entity()
        : m_Name("Unknown"), m_Score(87), m_Example(56) // Creates an Example instance with value 56
    {
        // Alternative way of assigning values after initialization (commented out)
        // m_Example = Example(56);
    }

    // Parameterized constructor: initializes entity name while leaving other attributes default
    Entity(const std::string& name) : m_Name(name) {
        // Alternative way of assigning values after initialization (commented out)
        // m_Name = name;
    }

    // Getter function to retrieve the entity's name
    const std::string GetName() const {
        return m_Name;
    }
};

int main() {
    // Creating an Entity object using the default constructor
    Entity e0;
    std::cout<<std::endl;
    return 0;
}
