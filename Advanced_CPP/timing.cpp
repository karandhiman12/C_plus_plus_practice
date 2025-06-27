#include <iostream>
#include <chrono>
#include <thread>

// A Timer struct that measures the duration between its creation and destruction
struct Timer {
    //std::chrono::time_point<std::chrono::steady_clock> start, end;
    // Using high_resolution_clock to capture precise start and end times
    std::chrono::high_resolution_clock::time_point start, end;

    // Duration will store the elapsed time as a float in seconds
    std::chrono::duration<float> duration; 

    // Constructor captures the start time when the Timer object is created
    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }

    // Destructor captures the end time and calculates the elapsed time
    ~Timer() {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;

        // Convert duration to milliseconds and display it
        float ms = duration.count() * 1000.0f;
        std::cout << "Timer took " << ms << "ms " << std::endl;
    }
};

// Function to demonstrate timing: prints "Hello" 100 times and measures time using the Timer object
void Function() {
    Timer timer; // Starts timing when this object is constructed
    for(int i = 0; i < 100; i++) {
        std::cout << "Hello\n";
    } // Timer object is destructed at the end of scope and displays elapsed time
}

int main() {
    using namespace std::literals::chrono_literals; // Enables use of literals like 1s for seconds

    Function(); // Call the function which measures its own execution time

    // Manually measure and display the duration of a 1-second sleep
    auto start = std::chrono::high_resolution_clock::now(); // Record start time
    std::this_thread::sleep_for(1s); // Pause the thread for 1 second
    auto end = std::chrono::high_resolution_clock::now(); // Record end time

    std::chrono::duration<float> duration = end - start; // Calculate elapsed time
    std::cout << duration.count() << "s \n"; // Output duration in seconds

    return 0;
}
