#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000000

// Συνάρτηση που υπολογίζει το μήκος της ακολουθίας Collatz για έναν αριθμό N
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

    if (N1 <= 0 || N2 > MAX_N || N1 < -MAX_N || N2 < -MAX_N) {
        printf("0\n"); // Έλεγχος για έγκυρα όρια. Εάν δεν είναι έγκυρα, το πρόγραμμα τυπώνει "0" και τερματίζει με κωδικό λάθους.
        return 1;
    }

    if (N1 < 0) {
        N1 = 1; // Εάν ο πρώτος αριθμός είναι αρνητικός, τον αλλάζουμε σε 1, όπως απαιτείται.
    }

    long long *memo = (long long *)calloc(MAX_N + 1, sizeof(long long));

    if (memo == NULL) {
        printf("Memory allocation error\n");
        return 1; // Έλεγχος για σφάλμα κατά την εκχώρηση μνήμης. Εάν υπάρχει σφάλμα, το πρόγραμμα τυπώνει "Memory allocation error" και τερματίζει με κωδικό λάθους.
    }

    long long maxCollatzLength = 0;
    for (long long i = N1; i <= N2; i++) {
        long long length = collatzLength(i, memo); // Κλήση της συνάρτησης collatzLength για κάθε αριθμό από N1 έως N2.
        if (length > maxCollatzLength) {
            maxCollatzLength = length; // Κρατάμε το μέγιστο μήκος της ακολουθίας Collatz.
        }
    }

    printf("%lld\n", maxCollatzLength); // Τύπωση του μέγιστου μήκους της ακολουθίας Collatz.

    free(memo); // Απελευθέρωση της δεσμευμένης μνήμης.

    return 0; // Το πρόγραμμα ολοκληρώνει την εκτέλεσή του χωρίς λάθη.
}
