#include <iostream>
#include <memory>

// Custom implementation of make_unique for C++11 (make_unique is available from C++14 onwards)
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) { 
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class Entity {
public:
    Entity() {
        std::cout << "Entity created.." << std::endl;
    }
    ~Entity() {
        std::cout << "Entity destroyed" << std::endl;
    }
};

int main() {
    // Using unique_ptr (Exclusive ownership, no shared ownership)
    std::unique_ptr<Entity> e1(new Entity()); // Manually constructing unique_ptr
    std::unique_ptr<Entity> e2 = make_unique<Entity>(); // Using make_unique (preferred)

    // Using shared_ptr (Shared ownership, multiple pointers can manage the same object)
    std::shared_ptr<Entity> sharedEntity(new Entity()); // Manually constructing shared_ptr

    std::shared_ptr<Entity> e0; // Empty shared_ptr
    {
        // Creating a shared_ptr using std::make_shared (efficient memory allocation)
        std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>(); 
        e0 = sharedEntity; // Another shared_ptr managing the same object

        // Using weak_ptr (Non-owning reference to shared_ptr, does not increase reference count)
        std::weak_ptr<Entity> e7 = sharedEntity; 

        // Weak pointers are useful to break cyclic dependencies in shared_ptr usage
    }

    // sharedEntity created inside the block goes out of scope, but e0 still owns it
    return 0;
}
