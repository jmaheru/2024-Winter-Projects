#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_CAPACITY 64

double stack[STACK_CAPACITY];

int stack_size = 0;

bool stack_push(double item) {
    if (stack_size == STACK_CAPACITY) {
        return false;

    } else {
        stack[stack_size] = item;
        stack_size++;
    }

    return true;
}

bool stack_peek(double *item) {
    if (stack_size == 0) {
        return false;

    } else {
        *item = stack[stack_size - 1];
    }

    return true;
}

bool stack_pop(double *item) {
    if (stack_size == 0) {
        return false;

    } else {
        *item = stack[stack_size - 1];
        stack_size--;
    }

    return true;
}

void stack_clear(void) {
    stack_size = 0;
}

void stack_print(void) {
    // make sure we don't print stack[0] when it is empty
    if (stack_size == 0) {
        return;
    }
    // print the first element with 10 decimal places
    printf("%.10f", stack[0]);
    // print the remaining elements (if any), with a space before each one
    for (int i = 1; i < stack_size; i++) {
        printf(" %.10f", stack[i]);
    }
}
