#include "operators.h"

#include "stack.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool apply_binary_operator(binary_operator_fn op) {
    if (stack_size < 2) {
        return false;
    }

    double x, y;

    assert(stack_pop(&y));
    assert(stack_pop(&x));

    double result = op(x, y);
    assert(stack_push(result));

    return true;
}

bool apply_unary_operator(unary_operator_fn op) {
    if (stack_size < 1) {
        return false;
    }

    double x;
    assert(stack_pop(&x));
    double result = op(x);
    assert(stack_push(result));

    return true;
}

//addition
double operator_add(double lhs, double rhs) {
    double val = lhs + rhs;
    return val;
}

//subtraction
double operator_sub(double lhs, double rhs) {
    double val = lhs - rhs;
    return val;
}

//multiplication
double operator_mul(double lhs, double rhs) {
    double val = lhs * rhs;
    return val;
}

//division
double operator_div(double lhs, double rhs) {
    double val = lhs / rhs;
    return val;
}

bool parse_double(const char *s, double *d) {
    char *endptr;
    double result = strtod(s, &endptr);

    if (endptr != s) {
        *d = result;
        return true;
    } else {
        return false;
    }
}
