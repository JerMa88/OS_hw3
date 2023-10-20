/*
    CLI instruction: gcc fibfib_multi.c -o fibfib_multi -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n; // Number of Fibonacci numbers
long long *fib_sequence; // Array to store Fibonacci sequence

void *generate_fibonacci(void *param) {
    fib_sequence[0] = 0;
    if (n > 1) {
        fib_sequence[1] = 1;
        for (int i = 2; i < n; i++) {
            fib_sequence[i] = fib_sequence[i-1] + fib_sequence[i-2];
        }
    }
    pthread_exit(0);
}

int main() {
    printf("Enter the number of Fibonacci numbers to generate: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    fib_sequence = malloc(n * sizeof(long long));

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&tid, &attr, generate_fibonacci, NULL);
    pthread_join(tid, NULL); // Wait for the thread to finish

    // Print the Fibonacci sequence
    for (int i = 0; i < n; i++) {
        printf("%lld ", fib_sequence[i]);
    }
    printf("\n");

    free(fib_sequence);
    return 0;
}
