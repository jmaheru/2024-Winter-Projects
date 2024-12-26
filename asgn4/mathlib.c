#include "mathlib.h"

#include "stack.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-14

double Abs(double x) {
    if (x < 0) {
        x = x * -1;
    }

    return x;
}

double Sqrt(double x) {
    // Check domain.
    if (x < 0) {
        return nan("nan");
    }

    double old = 0.0;
    double new = 1.0;

    while (Abs(old - new) > EPSILON) {
        // Specifically, this is the Babylonian method--a simplification of
        // Newton's method possible only for Sqrt(x).
        old = new;
        new = 0.5 * (old + (x / old));
    }

    return new;
}

double Sin(double x) {
    double val = 0;
    int loop = 0;

    x = fmod(x, (M_PI * 2));

    if (0 > x) {
        x = (x + (M_PI * 2));
    }

    while (true) {
        double exponent = x, sign = -1;

        if (loop == 0) {
            sign = 1;
        }

        for (int j = 1; j < (loop * 2) + 1; j++) {
            exponent = x * exponent;
        }

        for (int a = 1; a < loop; a++) {
            sign = sign * -1;
        }

        double fac = ((loop * 2) + 1), factorial = (fac) -1;

        for (int i = 1; i < (loop * 2) + 1; i++) {
            fac = fac * factorial;
            factorial--;
        }

        double val_int = (exponent / fac);

        if (EPSILON > Abs(val_int)) {
            return val;
        }

        loop++;
        val = val + (sign * val_int);
    }
}

double Cos(double x) {
    double val = 0;
    int loop = 0;

    x = fmod(x, (M_PI * 2));

    if (0 > x) {
        x = (x + (M_PI * 2));
    }

    while (true) {
        double factorial = (2 * loop), val_sign = -1, val_init = 0, exponent = x;

        if (loop == 0) {
            val_init = 1;
            exponent = 1;
            factorial = 1;
            val_sign = 1;
        }

        else {
            for (int j = 1; j < loop; j++) {
                val_sign = val_sign * -1;
            }

            for (int i = 1; i < (2 * loop); i++) {
                exponent = exponent * x;
            }

            double f_1 = factorial - 1;

            for (int i = 1; i < (2 * loop); i++) {
                factorial = (factorial * f_1);
                f_1--;
            }

            val_init = (exponent / factorial);

            if (EPSILON > Abs(val_init)) {
                return val;
            }
        }

        loop++;
        val = val + (val_init * (val_sign));
    }
}

double Tan(double x) {
    double val = Sin(x) / Cos(x);
    return val;
}
