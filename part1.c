// References:
// - https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>

// Global variables to store results
uint64_t sum_all = 0;
uint64_t sum_even = 0;

// Function for Thread 1 (Sum of all numbers)
void* calculate_sum_all(void* arg) {
    uint64_t n = *(uint64_t*)arg;
    uint64_t sum = 0;
    for (uint64_t i = 1; i <= n; i++) {
        sum += i;
    }
    sum_all = sum;
    pthread_exit(NULL);
}

// Function for Thread 2 (Sum of even numbers)
void* calculate_sum_even(void* arg) {
    uint64_t n = *(uint64_t*)arg;
    uint64_t sum = 0;
    for (uint64_t i = 2; i <= n; i += 2) {
        sum += i;
    }
    sum_even = sum;
    pthread_exit(NULL);
}

int main() {
    uint64_t n = 1000000000; // 1 billion
    pthread_t thread1, thread2;

    // start timers
    time_t start, end;
    // Start measuring time
    time(&start);
    // Create threads
    pthread_create(&thread1, NULL, calculate_sum_all, &n);
    pthread_create(&thread2, NULL, calculate_sum_even, &n);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Stop measuring time
    time(&end);
    double time_taken = (double)(end - start);

    // Display results
    printf("Sum of all numbers (1 to %lu): %lu\n", n, sum_all);
    printf("Sum of even numbers (1 to %lu): %lu\n", n, sum_even);
    printf("Ratio (Sum All / Sum Even): %.6f\n", (double)sum_all / sum_even);
    printf("Execution Time: %.2f seconds\n", time_taken);

    return 0;
}
