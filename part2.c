#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

int main() {
    uint64_t n = 1000000000; // 1 billion
    uint64_t sum_all = 0, sum_even = 0;

    // Start measuring time
    clock_t start = clock();

    // Compute sum of all numbers (same as Thread 1)
    for (uint64_t i = 1; i <= n; i++) {
        sum_all += i;
    }

    // Compute sum of even numbers (same as Thread 2)
    for (uint64_t i = 2; i <= n; i += 2) {
        sum_even += i;
    }

    // Stop measuring time
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    // Display results
    printf("Sum of all numbers (1 to %lu): %lu\n", n, sum_all);
    printf("Sum of even numbers (1 to %lu): %lu\n", n, sum_even);
    printf("Ratio (Sum All / Sum Even): %.6f\n", (double)sum_all / sum_even);
    printf("Execution Time: %.2f seconds\n", time_taken);

    return 0;
}
