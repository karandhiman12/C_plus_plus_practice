#include <iostream>
#include <thread>

// A simple function that simulates some work
void printNumbers(const std::string& threadName, int count) {
    for (int i = 1; i <= count; ++i) {
        std::cout << threadName << " prints: " << i << std::endl;
    }
}

int main() {
    // Launching two threads and passing different arguments
    std::thread t1(printNumbers, "Thread 1", 5);
    std::thread t2(printNumbers, "Thread 2", 5);

    // Wait for both threads to finish execution
    t1.join(); // blocks until thread t1 finishes
    t2.join(); // blocks until thread t2 finishes

    std::cout << "Both threads have completed their tasks." << std::endl;

    return 0;
}
