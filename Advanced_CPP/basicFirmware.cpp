#include <iostream>
#include <cstdint>
#include <thread>
#include <chrono>
#include <atomic>

// Hardware abstraction layer (HAL) - simulated for demonstration
namespace HAL {
    // Simulated memory-mapped registers
    volatile uint32_t* const GPIO_OUTPUT = reinterpret_cast<volatile uint32_t*>(0x40020000);
    volatile uint32_t* const ADC_DATA = reinterpret_cast<volatile uint32_t*>(0x40012000);
    volatile uint32_t* const TIMER_CONTROL = reinterpret_cast<volatile uint32_t*>(0x40000000);
    
    // GPIO pin definitions
    constexpr uint8_t LED_PIN = 13;
    constexpr uint8_t BUTTON_PIN = 2;
    
    // Simulated hardware functions
    void initGPIO() {
        std::cout << "[HAL] GPIO initialized\n";
    }
    
    void initADC() {
        std::cout << "[HAL] ADC initialized\n";
    }
    
    void initTimer() {
        std::cout << "[HAL] Timer initialized\n";
    }
    
    void digitalWrite(uint8_t pin, bool state) {
        // In real firmware, this would manipulate actual GPIO registers
        std::cout << "[HAL] Pin " << static_cast<int>(pin) << " set to " << (state ? "HIGH" : "LOW") << "\n";
    }
    
    bool digitalRead(uint8_t pin) {
        // Simulate button press every 5 seconds
        static auto start = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
        return (elapsed % 10) < 2; // Button "pressed" for 2 seconds every 10 seconds
    }
    
    uint16_t analogRead() {
        // Simulate varying ADC reading
        static uint16_t value = 512;
        value = (value + 17) % 1024; // Simple varying pattern
        return value;
    }
}

// Firmware system state
struct SystemState {
    std::atomic<bool> ledState{false};
    std::atomic<bool> systemRunning{true};
    std::atomic<uint16_t> sensorValue{0};
    std::atomic<uint32_t> buttonPressCount{0};
};

// Global system state
SystemState g_systemState;

// Task priorities (in real RTOS)
enum class TaskPriority : uint8_t {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3,
    CRITICAL = 4
};

// Basic task structure
struct Task {
    void (*function)();
    uint32_t periodMs;
    uint32_t lastRunMs;
    TaskPriority priority;
    const char* name;
};

// System initialization
void systemInit() {
    std::cout << "=== FIRMWARE BOOT SEQUENCE ===\n";
    
    // Hardware initialization
    HAL::initGPIO();
    HAL::initADC();
    HAL::initTimer();
    
    // System checks
    std::cout << "[BOOT] Running self-tests...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "[BOOT] All systems operational\n";
    std::cout << "[BOOT] Firmware version 1.0.0\n";
    std::cout << "===============================\n\n";
}

// Task implementations
void ledBlinkTask() {
    static uint32_t blinkCounter = 0;
    
    g_systemState.ledState = !g_systemState.ledState;
    HAL::digitalWrite(HAL::LED_PIN, g_systemState.ledState);
    
    blinkCounter++;
    if (blinkCounter % 10 == 0) {
        std::cout << "[LED] Heartbeat blink count: " << blinkCounter << "\n";
    }
}

void sensorReadTask() {
    uint16_t newValue = HAL::analogRead();
    g_systemState.sensorValue = newValue;
    
    // Alert if sensor value is out of normal range
    if (newValue > 800 || newValue < 200) {
        std::cout << "[SENSOR] WARNING: Sensor reading out of range: " << newValue << "\n";
    }
}

void buttonHandlerTask() {
    static bool lastButtonState = false;
    bool currentButtonState = HAL::digitalRead(HAL::BUTTON_PIN);
    
    // Detect button press (rising edge)
    if (currentButtonState && !lastButtonState) {
        g_systemState.buttonPressCount++;
        std::cout << "[BUTTON] Button pressed! Count: " << g_systemState.buttonPressCount.load() << "\n";
        
        // Toggle LED blink rate on button press
        std::cout << "[SYSTEM] Toggling LED blink rate\n";
    }
    
    lastButtonState = currentButtonState;
}

void systemMonitorTask() {
    static uint32_t monitorCounter = 0;
    
    if (++monitorCounter % 20 == 0) { // Every 10 seconds
        std::cout << "\n=== SYSTEM STATUS ===\n";
        std::cout << "LED State: " << (g_systemState.ledState ? "ON" : "OFF") << "\n";
        std::cout << "Sensor Value: " << g_systemState.sensorValue.load() << "\n";
        std::cout << "Button Presses: " << g_systemState.buttonPressCount.load() << "\n";
        std::cout << "System Uptime: " << (monitorCounter * 500) << "ms\n";
        std::cout << "====================\n\n";
    }
}

// Interrupt Service Routine (ISR) simulation
void criticalErrorISR() {
    // In real firmware, this would be called by hardware interrupt
    std::cout << "[ISR] CRITICAL ERROR DETECTED - EMERGENCY SHUTDOWN\n";
    g_systemState.systemRunning = false;
}

// Simple task scheduler
class TaskScheduler {
private:
    static constexpr size_t MAX_TASKS = 10;
    Task tasks[MAX_TASKS];
    size_t taskCount = 0;
    
public:
    void addTask(void (*func)(), uint32_t periodMs, TaskPriority priority, const char* name) {
        if (taskCount < MAX_TASKS) {
            tasks[taskCount] = {func, periodMs, 0, priority, name};
            taskCount++;
            std::cout << "[SCHEDULER] Added task: " << name << " (period: " << periodMs << "ms)\n";
        }
    }
    
    void run() {
        std::cout << "[SCHEDULER] Starting task scheduler with " << taskCount << " tasks\n\n";
        
        while (g_systemState.systemRunning) {
            auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now().time_since_epoch()).count();
            
            // Execute tasks based on their schedule
            for (size_t i = 0; i < taskCount; i++) {
                if (currentTime - tasks[i].lastRunMs >= tasks[i].periodMs) {
                    tasks[i].function();
                    tasks[i].lastRunMs = currentTime;
                }
            }
            
            // Simulate watchdog timer reset
            static uint32_t watchdogCounter = 0;
            if (++watchdogCounter % 1000 == 0) {
                std::cout << "[WATCHDOG] System alive - resetting watchdog timer\n";
            }
            
            // Sleep to prevent 100% CPU usage in simulation
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        std::cout << "\n[SCHEDULER] System shutdown initiated\n";
    }
};

// Power management simulation
void enterLowPowerMode() {
    std::cout << "[POWER] Entering low power mode...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "[POWER] Waking up from low power mode\n";
}

// Memory management for embedded systems
class MemoryPool {
private:
    static constexpr size_t POOL_SIZE = 1024;
    uint8_t memory[POOL_SIZE];
    bool allocated[POOL_SIZE];
    
public:
    void* allocate(size_t size) {
        for (size_t i = 0; i <= POOL_SIZE - size; i++) {
            bool canAllocate = true;
            for (size_t j = 0; j < size; j++) {
                if (allocated[i + j]) {
                    canAllocate = false;
                    break;
                }
            }
            
            if (canAllocate) {
                for (size_t j = 0; j < size; j++) {
                    allocated[i + j] = true;
                }
                std::cout << "[MEMORY] Allocated " << size << " bytes at offset " << i << "\n";
                return &memory[i];
            }
        }
        
        std::cout << "[MEMORY] ERROR: Out of memory!\n";
        return nullptr;
    }
    
    void deallocate(void* ptr, size_t size) {
        if (ptr >= memory && ptr < memory + POOL_SIZE) {
            size_t offset = static_cast<uint8_t*>(ptr) - memory;
            for (size_t i = 0; i < size; i++) {
                allocated[offset + i] = false;
            }
            std::cout << "[MEMORY] Deallocated " << size << " bytes at offset " << offset << "\n";
        }
    }
};

// Global memory pool
MemoryPool g_memoryPool;

// Main firmware application
int main() {
    // System initialization
    systemInit();
    
    // Create task scheduler
    TaskScheduler scheduler;
    
    // Add tasks with different priorities and periods
    scheduler.addTask(ledBlinkTask, 500, TaskPriority::LOW, "LED_BLINK");
    scheduler.addTask(sensorReadTask, 200, TaskPriority::MEDIUM, "SENSOR_READ");
    scheduler.addTask(buttonHandlerTask, 50, TaskPriority::HIGH, "BUTTON_HANDLER");
    scheduler.addTask(systemMonitorTask, 500, TaskPriority::LOW, "SYSTEM_MONITOR");
    
    // Demonstrate memory allocation
    void* buffer1 = g_memoryPool.allocate(64);
    void* buffer2 = g_memoryPool.allocate(128);
    
    std::cout << "\n[SYSTEM] Starting main firmware loop...\n";
    std::cout << "[SYSTEM] Press Ctrl+C to simulate system shutdown\n\n";
    
    // Simulate running for a limited time for demonstration
    std::thread mainLoop([&scheduler]() {
        scheduler.run();
    });
    
    // Simulate system running for 15 seconds
    std::this_thread::sleep_for(std::chrono::seconds(15));
    
    // Simulate shutdown
    std::cout << "\n[SYSTEM] Shutdown signal received\n";
    g_systemState.systemRunning = false;
    
    // Wait for main loop to finish
    mainLoop.join();
    
    // Cleanup
    g_memoryPool.deallocate(buffer1, 64);
    g_memoryPool.deallocate(buffer2, 128);
    
    std::cout << "\n[SYSTEM] Firmware shutdown complete\n";
    std::cout << "=== END OF FIRMWARE EXECUTION ===\n";
    
    return 0;
}

/*
FIRMWARE CONCEPTS DEMONSTRATED:

1. Hardware Abstraction Layer (HAL):
   - Memory-mapped register access
   - GPIO control functions
   - ADC reading functions

2. Real-time Task Scheduling:
   - Multiple concurrent tasks
   - Different task priorities
   - Periodic task execution

3. Interrupt Handling:
   - Simulated interrupt service routine (ISR)
   - Critical error handling

4. Memory Management:
   - Custom memory pool for deterministic allocation
   - Fixed-size memory management (no dynamic allocation)

5. System Monitoring:
   - Watchdog timer simulation
   - System status reporting
   - Error detection and handling

6. Power Management:
   - Low power mode simulation

7. Firmware Boot Sequence:
   - Hardware initialization
   - Self-tests
   - System startup

8. Embedded Programming Practices:
   - Volatile keyword for hardware registers
   - Atomic variables for thread-safe access
   - Fixed-size arrays and buffers
   - Minimal standard library usage

This code simulates firmware behavior and can be compiled and run
on a desktop system for educational purposes.
*/