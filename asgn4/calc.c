#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int lib = 0;

    if (argc > 1) {
        if (strcmp("-h", argv[1]) == 0) {
            printf(USAGE, argv[1]);
            exit(1);
        } else if (strcmp("-m", argv[1]) == 0) {
            lib = 1;
        } else {
            lib = 0;
        }
    }

    char expression[256];
    char unary_ops[] = "sctar", binary_ops[] = "+-*/%";
    fprintf(stderr, "> ");

    while (fgets(expression, 255, stdin)) {
        if (expression[0] == EOF) {
            break;
        }

        char *next = strchr(expression, '\n');
        if (next) {
            *next = 0;
        }

        char *token;
        token = strtok(expression, " \0");

        while (token != NULL) {
            double temp = 0;

            if (parse_double(token, &temp) == true) {
                if (stack_push(temp) == true) {
                    // If the value is successfully pushed onto the stack
                } else {
                    stack_clear();
                    fprintf(stderr, ERROR_NO_SPACE, (double) temp);
                    break;
                }
            } else if (strchr(unary_ops, token[0]) != NULL
                       || strchr(binary_ops, token[0]) != NULL) {
                if (token[0] == '+') {
                    if (apply_binary_operator(binary_operators['+']) == true) {
                    }
                    // If addition operation is successfully applied
                    else {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        stack_clear();
                    }
                }

                else if (token[0] == '-') {
                    if (apply_binary_operator(binary_operators['-']) == true) {
                    }
                    // If subtraction operation is successfully applied
                    else {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        stack_clear();
                    }
                }

                else if (token[0] == '*') {
                    if (apply_binary_operator(binary_operators['*']) == true) {
                    }
                    // If multiplication operation is successfully applied
                    else {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        stack_clear();
                    }
                }

                else if (token[0] == '/') {
                    if (apply_binary_operator(binary_operators['/']) == true) {
                    }
                    // If division operation is successfully applied
                    else {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        stack_clear();
                    }
                } else if (token[0] == '%') {
                    if (apply_binary_operator(binary_operators['%']) == true) {
                    }
                    // If modulo operation is successfully applied
                    else {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        stack_clear();
                    }
                }

                else if (token[0] == 's') {
                    if (lib == 0 && apply_unary_operator(my_unary_operators['s']) == true) {
                    }
                    // If sine operation is successfully applied using custom implementation
                    else if (lib == 1 && apply_unary_operator(libm_unary_operators['s']) == true) {
                    }
                    // If sine operation is successfully applied using library function
                    else {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        stack_clear();
                    }
                }

                else if (token[0] == 'c') {
                    if (lib == 0 && apply_unary_operator(my_unary_operators['c']) == true) {
                    }

                    else if (lib == 1 && apply_unary_operator(libm_unary_operators['c']) == true) {
                    }

                    else {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        stack_clear();
                    }
                }

                else if (token[0] == 't') {
                    if (lib == 0 && apply_unary_operator(my_unary_operators['t']) == true) {
                    }

                    else if (lib == 1 && apply_unary_operator(libm_unary_operators['t']) == true) {
                    }

                    else {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        stack_clear();
                    }
                }

                else if (token[0] == 'a') {
                    if (lib == 0 && apply_unary_operator(my_unary_operators['a']) == true) {
                    }

                    else if (lib == 1 && apply_unary_operator(libm_unary_operators['a']) == true) {
                    }

                    else {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        stack_clear();
                    }
                }

                else if (token[0] == 'r') {
                    if (lib == 0 && apply_unary_operator(my_unary_operators['r']) == true) {
                    }

                    else if (lib == 1 && apply_unary_operator(libm_unary_operators['r']) == true) {
                    }

                    else {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        stack_clear();
                    }
                }

            } else {
                if ((int) strlen(token) == 1) {
                    stack_clear();
                    fprintf(stderr, ERROR_BAD_CHAR, token[0]);
                    break;
                } else if ((int) strlen(token) > 1) {
                    stack_clear();
                    fprintf(stderr, ERROR_BAD_STRING, token);
                    break;
                }
            }
            token = strtok(NULL, " ");
        }

        if (stack_size > 0) {
            stack_print();
            printf("\n");
        }

        stack_clear();
        fprintf(stderr, "> ");
    }
    return 0;
}
