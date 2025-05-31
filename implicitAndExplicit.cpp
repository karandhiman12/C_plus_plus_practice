#include <iostream>
#include<string>

class Entity {
public:
    std::string m_Name;
    int m_Age;
public:
    explicit Entity(const std::string& name) : m_Name(name), m_Age(-1) {
        //explicit keyword disables the implicit conversion capability of a constructor 
    }
    explicit Entity(int age) : m_Name("Unknown"), m_Age(age){

    }
};

void PrintEntity(const Entity& etr) {

}

int main() {
    //PrintEntity(7);
    PrintEntity(Entity("Cherno"));
    std::string str = "Cherno";
    //Entity e1 = str;
    Entity e2 = (Entity)45;
    //Entity e3 = false;
    return 0;
    
}