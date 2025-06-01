#include <iostream>

class Entity {
public: 
    Entity() {
        std::cout<<"Entity created"<<std::endl;
    }
    ~Entity() {
        std::cout<<"Entity Destroyed"<<std::endl;
    }
};

int* createArray(){
    int* arr = new int[50];
    return arr;
}

class ScopedPtr {
private:
    Entity* m_Ptr;
public:
    ScopedPtr(Entity* ptr): m_Ptr(ptr) {}
    ~ScopedPtr() { delete m_Ptr; }
};

int main() {
    // int* ptr = createArray();
    // {
    //     Entity e;
    // }
    // Entity* p = new Entity();
    // delete ptr;

    {
        Entity* e0 = new Entity();
        ScopedPtr p(e0);
        ScopedPtr e = new Entity();
    }
    return 0;
}