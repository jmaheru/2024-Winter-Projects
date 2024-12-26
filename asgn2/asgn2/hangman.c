#include "hangman_helpers.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display(
    const char *secret, const char *correct_guesses, const char *incorrect_guesses, int incorrect) {
    printf("%s", CLEAR_SCREEN);
    printf("%s", arts[incorrect]);
    printf("\n");
    printf("\n");
    printf("    Phrase: ");

    for (size_t i = 0; i < strlen(secret); i++) {
        if (!is_lowercase_letter(secret[i])
            || string_contains_character(correct_guesses, secret[i])) {
            printf("%c", secret[i]);
        } else if (secret[i] == ' ' || secret[i] == '-' || secret[i] == '\'') {
            printf("%c", secret[i]);
        } else {
            printf("_");
        }
    }

    printf("\nEliminated: %s\n", incorrect_guesses);
    printf("\n");
}

bool win(const char *secret, const char *guesses) {
    bool letters = false;

    for (size_t i = 0; i < strlen(secret); i++) {
        if (is_lowercase_letter(secret[i]) && !string_contains_character(guesses, secret[i])) {
            letters = true;
            break;
        }
    }

    return !letters;
}

char make_it_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }

    return c;
}

void the_guess(const char *secret, char guess, char *correct_guesses, char *incorrect_guesses,
    int *incorrect) {
    char lower = make_it_lower(guess);

    while (string_contains_character(correct_guesses, lower)
           || string_contains_character(incorrect_guesses, lower)) {
        guess = read_letter();
        lower = make_it_lower(guess);
    }

    if (string_contains_character(secret, lower)) {
        if (!string_contains_character(correct_guesses, lower)) {
            correct_guesses[strlen(correct_guesses)] = lower;
        } else {
            return;
        }
    } else {
        (*incorrect)++;

        if (!string_contains_character(incorrect_guesses, lower)) {
            incorrect_guesses[strlen(incorrect_guesses)] = lower;
        }
    }

    size_t len_guesses = strlen(incorrect_guesses);
    for (size_t i = 0; i < len_guesses; i++) {
        for (size_t j = 0; j < len_guesses - i - 1; j++) {
            if (incorrect_guesses[j] > incorrect_guesses[j + 1]) {
                char temp = incorrect_guesses[j];
                incorrect_guesses[j] = incorrect_guesses[j + 1];
                incorrect_guesses[j + 1] = temp;
            }
        }
    }
    incorrect_guesses[len_guesses] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments!\n");
        printf("Usage: ./hangman <secret word or phrase>\n");
        printf("If the secret is multiple words, you must quote it!\n");
        return 1;
    }

    const char *secret = argv[1];

    if (!validate_secret(secret)) {
        return 1;
    }

    char correct_guesses[MAX_LENGTH] = { '\0' };
    char incorrect_guesses[MAX_LENGTH] = { '\0' };
    int incorrect = 0;

    while (incorrect < LOSING_MISTAKE) {
        display(secret, correct_guesses, incorrect_guesses, incorrect);

        if (win(secret, correct_guesses)) {
            printf("You win! The secret phrase was: %s\n", secret);
            return 0;
        }

        char guess = read_letter();

        the_guess(secret, guess, correct_guesses, incorrect_guesses, &incorrect);
    }

    display(secret, correct_guesses, incorrect_guesses, incorrect);
    printf("You lose! The secret phrase was: %s\n", secret);

    return 0;
}
