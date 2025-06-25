#include <iostream>   // For input and output streams
#include <thread>     // For using std::thread and std::this_thread

// A global flag to signal when work should stop
static bool s_Finished = false;

// Function to simulate background work
void DoWork() {
    using namespace std::literals::chrono_literals; // Enables use of 1s for time duration

    // Loop runs until s_Finished becomes true
    while (!s_Finished)
    {
        std::cout << "Working...\n";                 // Output a message to indicate work is happening
        std::this_thread::sleep_for(1s);             // Pause execution for 1 second
    }
}

int main() {
    std::thread worker(DoWork);   // Launch a new thread running the DoWork() function

    std::cin.get();               // Wait for user to press Enter
    s_Finished = true;           // Signal the worker thread to finish

    worker.join();               // Wait for the worker thread to complete execution
    std::cout << "Finished!\n";   // Output a final message

    std::cin.get();              // Wait for another Enter before program exits (optional pause)
}
