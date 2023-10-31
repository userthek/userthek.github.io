#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000000

// Συνάρτηση που υπολογίζει το μέγιστο μήκος της ακολουθίας Collatz για αριθμούς από N1 έως N2
long long maxCollatzLength(long long N1, long long N2, long long *memo) {
    long long maxLen = 0;

    for (long long i = N1; i <= N2; i++) {
        long long length = collatzLength(i, memo);
        if (length > maxLen) {
            maxLen = length;
        }
    }

    return maxLen;
}

// Υπόλογος του μήκους της ακολουθίας Collatz για έναν αριθμό N
long long collatzLength(long long N, long long *memo) {
    if (N == 1) {
        return 1; // Η ακολουθία Collatz για το 1 έχει μήκος 1.
    }

    if (N <= MAX_N && memo[N] != 0) {
        return memo[N]; // Εάν έχουμε ήδη υπολογίσει το μήκος, το επιστρέφουμε από τον πίνακα memo.
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
        // Αποθηκεύουμε το μήκος για τον αρχικό αριθμό στον πίνακα memo.
        memo[originalN] = length;
    }

    return length; // Επιστρέφουμε το μήκος της ακολουθίας Collatz.
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <N1> <N2>\n", argv[0]);
        return 1; // Έλεγχος για τον σωστό αριθμό εισόδων. Αν δεν είναι σωστός, το πρόγραμμα εξέρχεται με κωδικό λάθους.
    }

    long long N1 = atoll(argv[1]); // Μετατροπή της πρώτης εισόδου σε ακέραιο.
    long long N2 = atoll(argv[2]); // Μετατροπή της δεύτερης εισόδου σε ακέραιο.

    long long *memo = (long long *)calloc(MAX_N + 1, sizeof(long long));

    if (memo == NULL) {
        printf("Memory allocation error\n");
        return 1; // Έλεγχος για σφάλμα κατά την εκχώρηση μνήμης. Εάν υπάρχει σφάλμα, το πρόγραμμα τυπώνει "Memory allocation error" και τερματίζει με κωδικό λάθους.
    }

    long long maxLen = maxCollatzLength(N1, N2, memo);
    printf("%lld\n", maxLen); // Τύπωση του μέγιστου μήκους της ακολουθίας Collatz.

    free(memo); // Απελευθέρωση της δεσμευμένης μνήμης.

    return 0; // Ολοκλήρωση του προγράμματος χωρίς σφάλματα.
}




