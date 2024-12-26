#include "mathlib.h"

#include <math.h>
#include <stdio.h>

int main() {
    FILE *fp = fopen("trig_comparison.csv", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Print header
    fprintf(fp, "x, sin_diff, cos_diff, tan_diff\n");

    // Compute and print results
    for (double x = -10.0; x <= 10.0; x += 0.5) {
        double sin_diff = fabs(Sin(x) - sin(x));
        double cos_diff = fabs(Cos(x) - cos(x));
        double tan_diff = fabs(Tan(x) - tan(x));
        fprintf(fp, "%.25f, %.25f, %.25f, %.25f\n", x, sin_diff, cos_diff, tan_diff);
    }

    fclose(fp);
    return 0;
}
