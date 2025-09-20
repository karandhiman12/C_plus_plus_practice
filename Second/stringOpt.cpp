#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <string_view>

class StringOptimizationDemo {
private:
    static constexpr int ITERATIONS = 100000;
    
public:
    // 1. String concatenation: Bad vs Good approaches
    void demonstrateConcatenation() {
        std::cout << "\n=== String Concatenation Optimization ===\n";
        
        // BAD: Multiple string concatenations (creates many temporary objects)
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            std::string result = "Hello";
            result = result + " " + "World" + " " + std::to_string(i);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto bad_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // GOOD: Using reserve and compound assignment
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            std::string result;
            result.reserve(50); // Pre-allocate memory
            result += "Hello";
            result += " ";
            result += "World";
            result += " ";
            result += std::to_string(i);
        }
        end = std::chrono::high_resolution_clock::now();
        auto good_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Bad concatenation time: " << bad_time.count() << " μs\n";
        std::cout << "Good concatenation time: " << good_time.count() << " μs\n";
        std::cout << "Improvement: " << (double)bad_time.count() / good_time.count() << "x faster\n";
    }
    
    // 2. String building with stringstream vs direct concatenation
    void demonstrateStringBuilding() {
        std::cout << "\n=== String Building Optimization ===\n";
        
        std::vector<std::string> words = {"The", "quick", "brown", "fox", "jumps", "over", "lazy", "dog"};
        
        // Using stringstream (good for complex formatting)
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            std::stringstream ss;
            for (const auto& word : words) {
                ss << word << " ";
            }
            std::string result = ss.str();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto ss_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Using pre-allocated string (faster for simple concatenation)
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            std::string result;
            result.reserve(100); // Estimate total size
            for (const auto& word : words) {
                result += word;
                result += " ";
            }
        }
        end = std::chrono::high_resolution_clock::now();
        auto direct_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Stringstream time: " << ss_time.count() << " μs\n";
        std::cout << "Direct concatenation time: " << direct_time.count() << " μs\n";
        std::cout << "Direct is " << (double)ss_time.count() / direct_time.count() << "x faster\n";
    }
    
    // 3. String_view for read-only operations
    void demonstrateStringView() {
        std::cout << "\n=== String_view Optimization ===\n";
        
        std::string large_text = "This is a very long string that we want to process without copying. "
                                "String_view allows us to reference substrings without allocation. "
                                "This can significantly improve performance for read-only operations.";
        
        // BAD: Creating substrings (involves copying)
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            processStringCopy(large_text.substr(10, 20));
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto copy_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // GOOD: Using string_view (no copying)
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            std::string_view sv(large_text.data() + 10, 20);
            processStringView(sv);
        }
        end = std::chrono::high_resolution_clock::now();
        auto view_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Substring copy time: " << copy_time.count() << " μs\n";
        std::cout << "String_view time: " << view_time.count() << " μs\n";
        std::cout << "String_view is " << (double)copy_time.count() / view_time.count() << "x faster\n";
    }
    
    // 4. Move semantics for string operations
    void demonstrateMoveSemantics() {
        std::cout << "\n=== Move Semantics Optimization ===\n";
        
        // BAD: Copy semantics
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            std::string source = "This is a string that will be copied: " + std::to_string(i);
            std::string destination = source; // Copy
            processString(destination);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto copy_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // GOOD: Move semantics
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            std::string source = "This is a string that will be moved: " + std::to_string(i);
            std::string destination = std::move(source); // Move
            processString(destination);
        }
        end = std::chrono::high_resolution_clock::now();
        auto move_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Copy semantics time: " << copy_time.count() << " μs\n";
        std::cout << "Move semantics time: " << move_time.count() << " μs\n";
        std::cout << "Move is " << (double)copy_time.count() / move_time.count() << "x faster\n";
    }
    
    // 5. Small String Optimization demonstration
    void demonstrateSmallStringOptimization() {
        std::cout << "\n=== Small String Optimization ===\n";
        
        // Short strings (typically optimized by SSO)
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            std::string short_str = "Hello"; // Likely stored on stack
            processString(short_str);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto short_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Long strings (require heap allocation)
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            std::string long_str = "This is a very long string that exceeds the small string optimization threshold and requires heap allocation";
            processString(long_str);
        }
        end = std::chrono::high_resolution_clock::now();
        auto long_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Short string time: " << short_time.count() << " μs\n";
        std::cout << "Long string time: " << long_time.count() << " μs\n";
        std::cout << "Short strings are " << (double)long_time.count() / short_time.count() << "x faster\n";
    }
    
    // 6. String interning simulation
    void demonstrateStringInterning() {
        std::cout << "\n=== String Interning Simulation ===\n";
        
        std::vector<std::string> repeated_strings;
        
        // BAD: Creating duplicate strings
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            repeated_strings.push_back(std::string("REPEATED_STRING"));
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duplicate_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        repeated_strings.clear();
        
        // GOOD: Using shared string (simulated interning)
        static const std::string interned_string = "REPEATED_STRING";
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITERATIONS; ++i) {
            repeated_strings.push_back(interned_string); // Copy of same string
        }
        end = std::chrono::high_resolution_clock::now();
        auto interned_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Duplicate strings time: " << duplicate_time.count() << " μs\n";
        std::cout << "Interned strings time: " << interned_time.count() << " μs\n";
        std::cout << "Interning is " << (double)duplicate_time.count() / interned_time.count() << "x faster\n";
    }
    
    // Helper functions
    void processStringCopy(const std::string& str) {
        // Simulate some work with string copy
        volatile size_t len = str.length();
    }
    
    void processStringView(std::string_view sv) {
        // Simulate some work with string_view
        volatile size_t len = sv.length();
    }
    
    void processString(const std::string& str) {
        // Simulate some work
        volatile size_t len = str.length();
    }
    
    // 7. Best practices demonstration
    void demonstrateBestPractices() {
        std::cout << "\n=== Best Practices Summary ===\n";
        
        // 1. Use string_view for read-only parameters
        auto print_info = [](std::string_view name, std::string_view info) {
            std::cout << "Name: " << name << ", Info: " << info << "\n";
        };
        
        // 2. Use move semantics when transferring ownership
        auto create_greeting = [](std::string name) -> std::string {
            std::string greeting = "Hello, ";
            greeting += std::move(name); // Move name into greeting
            greeting += "!";
            return greeting; // RVO/NRVO will optimize this
        };
        
        // 3. Reserve capacity when size is known
        auto build_large_string = []() -> std::string {
            std::string result;
            result.reserve(1000); // Pre-allocate
            
            for (int i = 0; i < 100; ++i) {
                result += std::to_string(i);
                result += " ";
            }
            return result;
        };
        
        // 4. Use emplace operations when possible
        std::vector<std::string> strings;
        strings.reserve(10);
        strings.emplace_back("Direct construction"); // No temporary object
        
        // Demonstrate usage
        std::string name = "World";
        print_info("Demo", "String optimization techniques");
        std::string greeting = create_greeting(std::move(name));
        std::string large = build_large_string();
        
        std::cout << "Best practices demonstrated successfully!\n";
        std::cout << "Final greeting: " << greeting << "\n";
        std::cout << "Large string length: " << large.length() << "\n";
        std::cout << "Vector size: " << strings.size() << "\n";
    }
    
    void runAllDemonstrations() {
        std::cout << "C++ String Optimization Techniques Demo\n";
        std::cout << "======================================\n";
        std::cout << "Running " << ITERATIONS << " iterations for each test...\n";
        
        demonstrateConcatenation();
        demonstrateStringBuilding();
        demonstrateStringView();
        demonstrateMoveSemantics();
        demonstrateSmallStringOptimization();
        demonstrateStringInterning();
        demonstrateBestPractices();
        
        std::cout << "\n=== Key Takeaways ===\n";
        std::cout << "1. Use reserve() when you know approximate string size\n";
        std::cout << "2. Prefer += over + for string concatenation\n";
        std::cout << "3. Use string_view for read-only string parameters\n";
        std::cout << "4. Leverage move semantics with std::move()\n";
        std::cout << "5. Short strings benefit from Small String Optimization\n";
        std::cout << "6. Consider string interning for repeated strings\n";
        std::cout << "7. Use emplace operations to avoid temporary objects\n";
    }
};

int main() {
    StringOptimizationDemo demo;
    demo.runAllDemonstrations();
    return 0;
}