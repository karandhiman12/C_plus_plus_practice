#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>
#include <functional>

namespace MathEngine {
    std::mutex io_mutex; // Shared mutex for safe console output

    // Template function to apply any binary operation
    template<typename T>
    T applyOperation(T a, T b, const std::function<T(T, T)>& op) {
        return op(a, b);
    }

    // Task class that holds the operation and operands
    class Task {
    public:
        Task(int a, int b, std::function<int(int, int)> op, const std::string& name)
            : num1(a), num2(b), operation(op), taskName(name) {}

        void execute() {
            std::lock_guard<std::mutex> lock(io_mutex);
            int result = operation(num1, num2);
            std::cout << "[" << taskName << "] Result of operation: " << result << std::endl;
        }

    private:
        int num1, num2;
        std::function<int(int, int)> operation;
        std::string taskName;
    };
}

int main() {
    using namespace MathEngine;

    // Create shared pointers to Task objects
    std::vector<std::shared_ptr<Task>> tasks;
    tasks.push_back(std::make_shared<Task>(10, 5, [](int a, int b) { return a + b; }, "Addition"));
    tasks.push_back(std::make_shared<Task>(20, 4, [](int a, int b) { return a * b; }, "Multiplication"));
    tasks.push_back(std::make_shared<Task>(15, 3, [](int a, int b) { return a - b; }, "Subtraction"));
    tasks.push_back(std::make_shared<Task>(40, 8, [](int a, int b) { return a / b; }, "Division"));

    // Run each task in a separate thread
    std::vector<std::thread> threads;
    for (auto& task : tasks) {
        threads.emplace_back([task]() {
            task->execute();
        });
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
