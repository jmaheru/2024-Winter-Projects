#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_lowercase_letter(char c) {
    return (c >= 'a' && c <= 'z');
}

bool validate_secret(const char *secret) {
    size_t len_secret = strlen(secret);

    if (strlen(secret) > MAX_LENGTH) {
        printf("the secret phrase is over 256 characters\n");
        return false;
    }

    for (size_t i = 0; i < len_secret; i++) {
        if (!((secret[i] >= 'a' && secret[i] <= 'z') || secret[i] == ' ' || secret[i] == '-'
                || secret[i] == '\'')) {
            printf("invalid character: '%c'\n", secret[i]);
            printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
                   "apostrophes\n");
            return false;
        }
    }

    return true;
}

bool string_contains_character(const char *s, char c) {
    while (*s != '\0') {
        if (*s == c) {
            return true;
        }
        s++;
    }

    return false;
}

char read_letter(void) {
    int input;
    char letter;

    while (1) {
        printf("Guess a letter: ");
        input = getchar();

        while (getchar() != '\n')
            ;

        if (input >= 'a' && input <= 'z') {
            letter = (char) input;
            break;
        }
    }

    return letter;
}
