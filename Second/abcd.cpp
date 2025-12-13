//inheritance

#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        cout<<"Base Constructor\n";
    }
    virtual ~Base() {
        cout<<"Base Destructor\n";
    }
    virtual void memFunction() {
        cout<<"Base:: member function\n";
    }
};

class Derived : public Base {
public:
    Derived() {
        cout<<"Derived Constructor\n";
    }
    ~Derived() {
        cout<<"Derived Destructor\n";
    }
    void memFunction() override{
        cout<<"Derived:: member function\n";
    }
};

int main(){
    Base *instance = new Derived;
    instance->memFunction();
    delete instance;
    double a = 5.25;
    int b = static_cast<int>(a) + .29; //static casting
    cout<<b;
    return 0;
}
