#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    double a = 10;
    double b = 40;
    double c = 66;
    double d = -6;
    double e = 0;
    double f = 64;

    assert(Abs(d) == abs((int) d));
    assert(Sqrt(f) == sqrt((int) f));
    assert(Sin(e) == sin((int) e));
    assert(Cos(e) == cos((int) e));
    assert(Tan(e) == tan((int) e));

    assert(operator_add(a, b) == 50);
    assert(operator_sub(c, a) == 56);
    assert(operator_mul(a, b) == 400);
    assert(operator_div(a, b) == 0.25);

    stack_clear();
    assert(stack_size == 0);
    for (int x = 0; x < 15; x++) {
        double i = cos(x);
        printf("%.10f\n", i);
    }

    return 0;
}
