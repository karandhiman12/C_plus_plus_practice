#include <iostream>
#include <thread>

void DoWork() {

}
int main() {
    std::thread worker(DoWork);
    worker.join();
    std::cin.get();
    return 0;
}