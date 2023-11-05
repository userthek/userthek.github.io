#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) {
    return 5 * pow(x, 5) - 4 * pow(x, 4) + 3 * pow(x, 3) - 2 * pow(x, 2) + x - 5;
}

double df(double x) {
    return 25 * pow(x, 4) - 16 * pow(x, 3) + 9 * pow(x, 2) - 4 * x + 1;
}

int main(int argc, char *argv[]) {
    if (argc != 7) {
        printf("Usage: %s a b c d e f\n", argv[0]);
        return 1;
    }

    double a = strtod(argv[1], NULL);
    double b = strtod(argv[2], NULL);
    double c = strtod(argv[3], NULL);
    double d = strtod(argv[4], NULL);
    double e = strtod(argv[5], NULL);
    double f = strtod(argv[6], NULL);

    double x0 = 1.0; // Initial guess
    double tolerance = 1e-6;
    double x = x0;
    int maxIterations = 1000;

    int iter = 0;
    while (iter < maxIterations) {
        double x_next = x - f(x) / df(x);
        if (fabs(x_next - x) < tolerance) {
            printf("%.2f\n", x_next);
            return 0;
        }
        if (!isfinite(x_next)) {
            printf("nan\n");
            return 0;
        }
        x = x_next;
        iter++;
    }

    if (iter >= maxIterations) {
        printf("incomplete\n");
    }

    return 0;
}
