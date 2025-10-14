#include <iostream>
#include <thread>

static bool s_Free = false;

void doWork() {
    using namespace std::literals::chrono_literals;
    std::cout<<"Start id: "<<std::this_thread::get_id()<<std::endl;
    while(!s_Free) {
        std::cout<<"Working\n";
        std::this_thread::sleep_for(1s);
    }
   
}

int main() {
    std::thread worker(doWork);
    std::cin.get();
    s_Free = true;
    worker.join();
    std::cout<<"Finish id: "<<std::this_thread::get_id()<<std::endl;
    std::cin.get();
    return 0;
}