#include <iostream>

class Engine {};
class Wheels { public: int count; };

class Car: public Engine, public Wheels {};
struct Bike: private Engine, Wheels {};

int main() {
    Car myCar;
    myCar.count = 4;
    std::cout<<myCar.count<<std::endl;

    Bike myBike;
    myBike.count = 5;
    std::cout<<myBike.count<<std::endl;
}