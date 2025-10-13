#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Shared resources
int shared_counter = 0;
int buffer[5];
int buffer_index = 0;

// Mutex for protecting shared_counter
pthread_mutex_t counter_mutex;

// Semaphores for producer-consumer problem
sem_t empty_slots;  // Counts empty buffer slots
sem_t full_slots;   // Counts full buffer slots
pthread_mutex_t buffer_mutex;

// ===== MUTEX DEMONSTRATION =====
void* increment_counter(void* arg) {
    int thread_id = *(int*)arg;
    
    for (int i = 0; i < 5; i++) {
        // Lock mutex before accessing shared resource
        pthread_mutex_lock(&counter_mutex);
        
        int temp = shared_counter;
        printf("Thread %d: Read counter = %d\n", thread_id, temp);
        usleep(100000); // Simulate some work (100ms)
        temp++;
        shared_counter = temp;
        printf("Thread %d: Updated counter = %d\n", thread_id, shared_counter);
        
        // Unlock mutex after done
        pthread_mutex_unlock(&counter_mutex);
        
        usleep(50000); // Sleep briefly between iterations
    }
    
    return NULL;
}

// ===== SEMAPHORE DEMONSTRATION (Producer-Consumer) =====
void* producer(void* arg) {
    int producer_id = *(int*)arg;
    
    for (int i = 0; i < 3; i++) {
        int item = producer_id * 10 + i;
        
        // Wait for an empty slot
        sem_wait(&empty_slots);
        
        // Lock buffer for exclusive access
        pthread_mutex_lock(&buffer_mutex);
        
        buffer[buffer_index] = item;
        printf("Producer %d: Produced item %d at index %d\n", 
               producer_id, item, buffer_index);
        buffer_index++;
        
        pthread_mutex_unlock(&buffer_mutex);
        
        // Signal that there's a new full slot
        sem_post(&full_slots);
        
        usleep(200000); // Sleep 200ms between productions
    }
    
    return NULL;
}

void* consumer(void* arg) {
    int consumer_id = *(int*)arg;
    
    for (int i = 0; i < 3; i++) {
        // Wait for a full slot
        sem_wait(&full_slots);
        
        // Lock buffer for exclusive access
        pthread_mutex_lock(&buffer_mutex);
        
        buffer_index--;
        int item = buffer[buffer_index];
        printf("Consumer %d: Consumed item %d from index %d\n", 
               consumer_id, item, buffer_index);
        
        pthread_mutex_unlock(&buffer_mutex);
        
        // Signal that there's a new empty slot
        sem_post(&empty_slots);
        
        usleep(300000); // Sleep 300ms between consumptions
    }
    
    return NULL;
}

int main() {
    pthread_t threads[6];
    int thread_ids[6] = {1, 2, 3, 4, 5, 6};
    
    // Initialize mutex
    pthread_mutex_init(&counter_mutex, NULL);
    pthread_mutex_init(&buffer_mutex, NULL);
    
    // Initialize semaphores
    sem_init(&empty_slots, 0, 5);  // Buffer has 5 empty slots initially
    sem_init(&full_slots, 0, 0);   // Buffer has 0 full slots initially
    
    printf("========== MUTEX DEMONSTRATION ==========\n");
    printf("Two threads incrementing a shared counter with mutex protection\n\n");
    
    // Create threads that increment counter (mutex demo)
    pthread_create(&threads[0], NULL, increment_counter, &thread_ids[0]);
    pthread_create(&threads[1], NULL, increment_counter, &thread_ids[1]);
    
    // Wait for counter threads to finish
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    
    printf("\nFinal counter value: %d (Expected: 10)\n", shared_counter);
    
    printf("\n========== SEMAPHORE DEMONSTRATION ==========\n");
    printf("Producer-Consumer problem with bounded buffer (size 5)\n\n");
    
    // Create producer and consumer threads (semaphore demo)
    pthread_create(&threads[2], NULL, producer, &thread_ids[2]);
    pthread_create(&threads[3], NULL, producer, &thread_ids[3]);
    pthread_create(&threads[4], NULL, consumer, &thread_ids[4]);
    pthread_create(&threads[5], NULL, consumer, &thread_ids[5]);
    
    // Wait for producer-consumer threads to finish
    for (int i = 2; i < 6; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\n========== DEMO COMPLETE ==========\n");
    
    // Cleanup
    pthread_mutex_destroy(&counter_mutex);
    pthread_mutex_destroy(&buffer_mutex);
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    
    return 0;
}