#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

// ===== EXAMPLE 1: Volatile with Signal Handlers =====
volatile sig_atomic_t signal_received = 0;

void signal_handler(int signum) {
    signal_received = 1;
    printf("Signal received! Setting flag.\n");
}

void demo_signal_handler() {
    printf("========== VOLATILE WITH SIGNALS ==========\n");
    printf("Without 'volatile', compiler might optimize away flag checks\n\n");
    
    signal(SIGINT, signal_handler);
    
    printf("Press Ctrl+C to send signal (or wait 5 seconds)...\n");
    
    int timeout = 0;
    // Without volatile, compiler might cache signal_received in a register
    // and never see the update from the signal handler
    while (!signal_received && timeout < 50) {
        usleep(100000); // 100ms
        timeout++;
    }
    
    if (signal_received) {
        printf("Signal flag detected! Continuing...\n\n");
    } else {
        printf("Timeout reached. Continuing...\n\n");
    }
    
    // Reset for next example
    signal(SIGINT, SIG_DFL);
}

// ===== EXAMPLE 2: Volatile with Multi-threading =====
volatile int shared_flag = 0;
int non_volatile_flag = 0;

void* thread_modifier(void* arg) {
    sleep(1);
    printf("Thread: Setting flags to 1\n");
    shared_flag = 1;
    non_volatile_flag = 1;
    return NULL;
}

void demo_multithreading() {
    printf("========== VOLATILE WITH THREADS ==========\n");
    printf("Demonstrates volatile with shared memory between threads\n\n");
    
    pthread_t thread;
    pthread_create(&thread, NULL, thread_modifier, NULL);
    
    printf("Main: Waiting for volatile flag...\n");
    
    // Volatile ensures this loop always reads from memory
    int checks = 0;
    while (shared_flag == 0 && checks < 30) {
        checks++;
        usleep(100000); // 100ms
    }
    
    if (shared_flag) {
        printf("Main: Volatile flag detected after %d checks!\n", checks);
    }
    
    pthread_join(thread, NULL);
    printf("\n");
}

// ===== EXAMPLE 3: Memory-Mapped I/O Simulation =====
// Simulating hardware register access
typedef struct {
    volatile unsigned int status_register;
    volatile unsigned int data_register;
    volatile unsigned int control_register;
} DeviceRegisters;

void demo_memory_mapped_io() {
    printf("========== VOLATILE WITH MEMORY-MAPPED I/O ==========\n");
    printf("Simulating hardware register access where values change externally\n\n");
    
    DeviceRegisters* device = (DeviceRegisters*)malloc(sizeof(DeviceRegisters));
    
    device->status_register = 0;
    device->control_register = 0;
    
    printf("Writing to control register...\n");
    device->control_register = 0x01; // Start operation
    
    printf("Reading status register (simulated hardware updates)...\n");
    
    // Simulate hardware updating the status register
    // In real hardware, this would change without CPU intervention
    int iterations = 0;
    while (iterations < 3) {
        // Volatile prevents compiler from caching the value
        printf("Status: 0x%02X\n", device->status_register);
        
        // Simulate external hardware update
        device->status_register = (device->status_register + 1) & 0xFF;
        
        usleep(500000); // 500ms
        iterations++;
    }
    
    printf("Operation complete!\n\n");
    free(device);
}

// ===== EXAMPLE 4: Demonstrating Compiler Optimization =====
void demo_optimization_difference() {
    printf("========== COMPILER OPTIMIZATION BEHAVIOR ==========\n");
    printf("Showing how volatile prevents optimization\n\n");
    
    volatile int vol_value = 5;
    int normal_value = 5;
    
    printf("Initial values: vol_value=%d, normal_value=%d\n", vol_value, normal_value);
    
    // With volatile: compiler MUST read from memory each time
    printf("\nReading volatile value 3 times:\n");
    for (int i = 0; i < 3; i++) {
        int x = vol_value; // Forces memory read
        printf("  Read #%d: %d (memory read guaranteed)\n", i+1, x);
    }
    
    // Without volatile: compiler might optimize to single read
    printf("\nReading non-volatile value 3 times:\n");
    for (int i = 0; i < 3; i++) {
        int x = normal_value; // Might be optimized
        printf("  Read #%d: %d (might be cached in register)\n", i+1, x);
    }
    
    printf("\nNote: With optimization flags (-O2, -O3), the compiler\n");
    printf("might cache 'normal_value' but must always read 'vol_value'\n\n");
}

// ===== EXAMPLE 5: Volatile vs Atomic Operations =====
void demo_volatile_limitations() {
    printf("========== VOLATILE LIMITATIONS ==========\n");
    printf("Important: volatile != thread-safe!\n\n");
    
    volatile int counter = 0;
    
    printf("Volatile does NOT guarantee atomicity:\n");
    printf("  counter++ is typically three operations:\n");
    printf("  1. Read counter from memory\n");
    printf("  2. Increment value\n");
    printf("  3. Write back to memory\n");
    printf("\n");
    printf("These operations are NOT atomic even with 'volatile'!\n");
    printf("For thread safety, use:\n");
    printf("  - Mutexes (pthread_mutex_t)\n");
    printf("  - Atomic operations (stdatomic.h in C11)\n");
    printf("  - Semaphores\n\n");
    
    printf("Volatile ONLY ensures:\n");
    printf("  - No optimization of reads/writes\n");
    printf("  - Reads/writes happen in order\n");
    printf("  - Values are read from memory each time\n\n");
}

// ===== MAIN =====
int main() {
    printf("============================================\n");
    printf("   VOLATILE KEYWORD DEMONSTRATION IN C\n");
    printf("============================================\n\n");
    
    demo_signal_handler();
    demo_multithreading();
    demo_memory_mapped_io();
    demo_optimization_difference();
    demo_volatile_limitations();
    
    printf("========== KEY TAKEAWAYS ==========\n");
    printf("Use 'volatile' when:\n");
    printf("  ✓ Accessing memory-mapped hardware registers\n");
    printf("  ✓ Variables modified by signal handlers\n");
    printf("  ✓ Variables shared with ISRs (embedded systems)\n");
    printf("  ✓ Preventing compiler optimization on specific variables\n");
    printf("\n");
    printf("Don't rely on 'volatile' for:\n");
    printf("  ✗ Thread synchronization (use mutexes/atomics)\n");
    printf("  ✗ Atomic operations (not guaranteed)\n");
    printf("  ✗ Memory barriers (use proper sync primitives)\n");
    printf("\n");
    
    return 0;
}