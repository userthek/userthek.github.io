#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000000

// Συνάρτηση που υπολογίζει το μήκος της ακολουθίας Collatz για έναν αριθμό N
long long collatzLength(long long N, long long *memo) {
    if (N == 1) {
        return 1;
    }

    if (N <= MAX_N && memo[N] != 0) {
        return memo[N];
    }

    long long length = 1;
    long long originalN = N;

    while (N != 1) {
        if (N <= MAX_N && memo[N] != 0) {
            // Αν βρούμε αποθηκευμένο αποτέλεσμα, προσθέτουμε το μήκος και τερματίζουμε
            length += memo[N] - 1; // Μείωνουμε 1 γιατί το length ήδη ξεκινάει από 1
            break;
        }
        if (N % 2 == 0) {
            N /= 2;
        } else {
            N = 3 * N + 1;
        }
        length++;
    }

    if (originalN <= MAX_N) {
        // Αποθηκεύουμε το μήκος για τον αρχικό αριθμό
        memo[originalN] = length;
    }

    return length;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <N1> <N2>\n", argv[0]);
        return 1;
    }

    long long N1 = atoll(argv[1]);
    long long N2 = atoll(argv[2);

    if (N1 <= 0 || N2 <= 0 || N1 > MAX_N || N2 > MAX_N) {
        printf("Input numbers must be positive and within the acceptable range.\n");
        return 1;
    }

    long long *memo = (long long *)calloc(MAX_N + 1, sizeof(long long));

    if (memo == NULL) {
        printf("Memory allocation error\n");
        return 1;
    }

    long long maxCollatzLength = 0;
    for (long long i = N1; i <= N2; i++) {
        long long length = collatzLength(i, memo);
        if (length > maxCollatzLength) {
            maxCollatzLength = length;
        }
    }

    printf("%lld\n", maxCollatzLength);

    free(memo);

    return 0;
}
