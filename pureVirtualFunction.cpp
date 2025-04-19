#include <iostream>
using namespace std; //don't recommend to use on global level but here using cause it wont do any harm

class Printable {
    public:
        virtual void GetClassName() = 0;
};

class Entity: public Printable {
    public:
    virtual void getName() { cout<<"Entity"<<endl; }
    void GetClassName() override { cout<<"Entity"<<endl; }
};

class Player: public Entity {
    public:
    virtual void getName() { cout<<"Player"<<endl; }
    void GetClassName() override { cout<<"Player"<<endl; }
};
void Print(Printable *obj) {
    obj->GetClassName();
}

int main() {
    Entity* e = new Entity();
    Player *p = new Player();
    Entity *e1 = p;

    Print(e);
    Print(p);
    Print(e1);

    return 0;
}