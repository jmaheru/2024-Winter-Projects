#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *testString = "jasonfunniest";
    char testChar = 'a';

    if (string_contains_character(testString, testChar)) {
        printf("'%c' is in the string.\n", testChar);

    } else {
        printf("'%c' is NOT in the string.\n", testChar);
    }

    char guessedLetter = read_letter();

    printf("You guessed: %c\n", guessedLetter);

    char testLowercase = 'c';

    if (is_lowercase_letter(testLowercase)) {
        printf("'%c' is a lowercase letter.\n", testLowercase);

    } else {
        printf("'%c' is NOT a lowercase letter.\n", testLowercase);
    }

    const char *validSecret = "hangman-game";

    if (validate_secret(validSecret)) {
        printf("'%s' is a valid secret phrase.\n", validSecret);
    }

    const char *invalidSecret = "Jason96";

    if (!validate_secret(invalidSecret)) {
        printf("'%s' is NOT a valid secret phrase.\n", invalidSecret);
    }

    return 0;
}
