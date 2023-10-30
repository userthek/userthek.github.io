#include <stdio.h>
#include <stdlib.h>

long long collatzLength(long long N) {
    long long length = 1;

    while (N != 1) {
        if (N % 2 == 0) {
            N /= 2;
        } else {
            N = 3 * N + 1;
        }
        length++;
    }

    return length;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <N1> <N2>\n", argv[0]);
        return 1;
    }

    long long N1 = atoll(argv[1]);
    long long N2 = atoll(argv[2]);

    if (N1 <= 0 || N2 <= 0 || N1 > 100000000 || N2 > 100000000) {
        printf("0\n");
        return 1;
    }

    long long maxCollatzLength = 0;
    
    if (N1 > N2) {
        // Swap N1 and N2 if N1 is greater than N2
        long long temp = N1;
        N1 = N2;
        N2 = temp;
    }

    for (long long i = N1; i <= N2; i++) {
        long long length = collatzLength(i);
        if (length > maxCollatzLength) {
            maxCollatzLength = length;
        }
    }

    printf("%lld\n", maxCollatzLength);

    return 0;
}
