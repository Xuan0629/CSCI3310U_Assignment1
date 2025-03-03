// References:
// - https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>


// Global variables to store results
unsigned long long sum_all = 0;
unsigned long long sum_even = 0;

// Function for Thread 1 (Sum of all numbers)
void* calculate_sum_all(void* arg) {
    unsigned long long n = *(unsigned long long*)arg;
    unsigned long long sum = 0;
    for (unsigned long long i = 1; i <= n; i++) {
        sum += i;
    }
    sum_all = sum;
    pthread_exit(NULL);
}

// Function for Thread 2 (Sum of even numbers)
void* calculate_sum_even(void* arg) {
    unsigned long long n = *(unsigned long long*)arg;
    unsigned long long sum = 0;
    for (unsigned long long i = 2; i <= n; i += 2) {
        sum += i;
    }
    sum_even = sum;
    pthread_exit(NULL);
}

int main() {
    uint64_t n = 1000000000; // 1 billion
    pthread_t thread1, thread2;

    // Start timers
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Create threads
    pthread_create(&thread1, NULL, calculate_sum_all, &n);
    pthread_create(&thread2, NULL, calculate_sum_even, &n);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Stop measuring time
    gettimeofday(&end, NULL);
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec -
                              start.tv_usec)) * 1e-6;

    // Display results
    printf("Sum of all numbers (1 to %lu): %lu\n", n, sum_all);
    printf("Sum of even numbers (1 to %lu): %lu\n", n, sum_even);
    printf("Ratio (Sum All / Sum Even): %.6f\n", (double)sum_all / sum_even);
    printf("Execution Time: %.2f seconds\n", time_taken);

    return 0;
}
