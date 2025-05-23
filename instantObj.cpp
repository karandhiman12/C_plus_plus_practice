#include <iostream>
using namespace std;

class Entity {
private:
    string m_Name;
public:
    Entity(const string& name) : m_Name(name) {
        cout << "Entity " << m_Name << " Created\n";
    }
    ~Entity() {
        cout << "Entity " << m_Name << " Destroyed\n";
    }
    void PrintName() const {
        cout << "Name: " << m_Name << endl;
    }
};

int main() {
    cout << "Stack Object:\n";
    {
        Entity stackEntity("Stack"); // Object is created on stack
        stackEntity.PrintName();
    } // Automatically destroyed when scope ends
    //Entity *p;
    cout << "\nHeap Object:\n";
    {
        Entity* heapEntity = new Entity("Heap"); // Object is allocated on heap
        heapEntity->PrintName();
        //p = heapEntity;
        delete heapEntity; // Manually deleted (or else memory leak!)
    }
    //p->PrintName(); accessing heap outside block if not manually deleted
    //delete p;
    return 0;
}
