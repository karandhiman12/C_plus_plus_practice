#include <iostream>
#include <thread>

// Global flag to control the worker thread's loop
static bool s_Free = false;

// Function executed by the worker thread
void doWork() {
    using namespace std::literals::chrono_literals; // Enables use of time literals like 1s
    std::cout << "Start id: " << std::this_thread::get_id() << std::endl; // Print thread ID

    // Loop until s_Free becomes true
    while (!s_Free) {
        std::cout << "Working\n"; // Simulate work
        std::this_thread::sleep_for(1s); // Pause for 1 second
    }
}

// Entry point of the program
int main() {
    // Launch a new thread that runs doWork
    std::thread worker(doWork);

    // Wait for user input to proceed
    std::cin.get();

    // Signal the worker thread to stop
    s_Free = true;

    // Wait for the worker thread to finish
    worker.join();

    // Print the main thread ID
    std::cout << "Finish id: " << std::this_thread::get_id() << std::endl;

    // Wait for another user input before exiting
    std::cin.get();

    return 0;
}
