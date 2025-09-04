#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <random>

// Simulate a time-consuming task
int heavy_computation(int id, int duration_ms) {
    std::cout << "Task " << id << " started on thread " 
              << std::this_thread::get_id() << std::endl;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));
    
    int result = id * id + duration_ms;
    std::cout << "Task " << id << " completed with result: " << result << std::endl;
    
    return result;
}

// Async function that might throw an exception
int risky_computation(int value) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    if (value < 0) {
        throw std::invalid_argument("Negative values not allowed!");
    }
    
    return value * 2;
}

// Function to demonstrate std::promise and std::future
void promise_example() {
    std::cout << "\n=== Promise/Future Example ===" << std::endl;
    
    std::promise<std::string> promise;
    std::future<std::string> future = promise.get_future();
    
    // Launch a thread that will set the promise value
    std::thread worker([&promise]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        promise.set_value("Hello from worker thread!");
    });
    
    std::cout << "Main thread waiting for result..." << std::endl;
    
    // Wait for the result
    std::string result = future.get();
    std::cout << "Received: " << result << std::endl;
    
    worker.join();
}

// Function to demonstrate std::async with different launch policies
void async_policies_example() {
    std::cout << "\n=== Async Launch Policies Example ===" << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // std::launch::async - guaranteed to run asynchronously
    auto future1 = std::async(std::launch::async, heavy_computation, 1, 800);
    
    // std::launch::deferred - lazy evaluation (runs when get() is called)
    auto future2 = std::async(std::launch::deferred, heavy_computation, 2, 600);
    
    // Default policy (implementation decides)
    auto future3 = std::async(heavy_computation, 3, 400);
    
    std::cout << "All async tasks launched" << std::endl;
    
    // Get results (this will trigger deferred execution for future2)
    int result1 = future1.get();
    int result2 = future2.get(); // Deferred task runs here
    int result3 = future3.get();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Total results: " << result1 + result2 + result3 
              << " (completed in " << duration.count() << "ms)" << std::endl;
}

// Function to demonstrate exception handling with futures
void exception_handling_example() {
    std::cout << "\n=== Exception Handling Example ===" << std::endl;
    
    // Launch tasks that might throw exceptions
    auto safe_future = std::async(std::launch::async, risky_computation, 10);
    auto risky_future = std::async(std::launch::async, risky_computation, -5);
    
    try {
        int safe_result = safe_future.get();
        std::cout << "Safe computation result: " << safe_result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Safe computation failed: " << e.what() << std::endl;
    }
    
    try {
        int risky_result = risky_future.get();
        std::cout << "Risky computation result: " << risky_result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Risky computation failed: " << e.what() << std::endl;
    }
}

// Function to demonstrate parallel processing with multiple futures
void parallel_processing_example() {
    std::cout << "\n=== Parallel Processing Example ===" << std::endl;
    
    const int num_tasks = 5;
    std::vector<std::future<int>> futures;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Launch multiple async tasks
    for (int i = 0; i < num_tasks; ++i) {
        int duration = 300 + (i * 100); // Varying durations
        futures.push_back(
            std::async(std::launch::async, heavy_computation, i + 1, duration)
        );
    }
    
    std::cout << "Launched " << num_tasks << " parallel tasks" << std::endl;
    
    // Collect results as they complete
    int total_result = 0;
    for (auto& future : futures) {
        total_result += future.get();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "All parallel tasks completed. Total result: " << total_result 
              << " (in " << duration.count() << "ms)" << std::endl;
}

// Function to demonstrate future status checking
void future_status_example() {
    std::cout << "\n=== Future Status Checking Example ===" << std::endl;
    
    auto future = std::async(std::launch::async, heavy_computation, 99, 2000);
    
    // Check future status while it's running
    for (int i = 0; i < 10; ++i) {
        auto status = future.wait_for(std::chrono::milliseconds(300));
        
        switch (status) {
            case std::future_status::ready:
                std::cout << "Task completed! Result: " << future.get() << std::endl;
                return;
            case std::future_status::timeout:
                std::cout << "Still waiting... (" << (i + 1) << "/10)" << std::endl;
                break;
            case std::future_status::deferred:
                std::cout << "Task is deferred" << std::endl;
                break;
        }
    }
    
    // If we get here, force completion
    std::cout << "Forcing completion... Result: " << future.get() << std::endl;
}

int main() {
    std::cout << "C++ Asynchronous Programming Demonstration" << std::endl;
    std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl;
    
    // Run all examples
    promise_example();
    async_policies_example();
    exception_handling_example();
    parallel_processing_example();
    future_status_example();
    
    std::cout << "\n=== All async examples completed! ===" << std::endl;
    
    return 0;
}