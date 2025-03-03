#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>

int main(int argc, char* argv[]) {
    unsigned long long n = 1000000000; // 1 billion
    unsigned long long sum_all = 0, sum_even = 0;
    if (argc >= 2) {
        n = strtoull(argv[1], NULL, 10);
    }
    // Start timers
    struct timeval start, end;
    gettimeofday(&start, NULL);
    // Compute sum of all numbers (same as Thread 1)
    for (unsigned long long i = 1; i <= n; i++) {
        sum_all += i;
    }

    // Compute sum of even numbers (same as Thread 2)
    for (unsigned long long i = 2; i <= n; i += 2) {
        sum_even += i;
    }

    // Stop measuring time
    gettimeofday(&end, NULL);
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec -
                              start.tv_usec)) * 1e-6;

    // Display results
    printf("Sum of all numbers (1 to %llu): %llu\n", n, sum_all);
    printf("Sum of even numbers (1 to %llu): %llu\n", n, sum_even);
    printf("Ratio (Sum All / Sum Even): %.6f\n", (double)sum_all / sum_even);
    printf("Execution Time: %.2f seconds\n", time_taken);

    return 0;
}
