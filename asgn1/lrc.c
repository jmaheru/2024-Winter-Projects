#include "names.h"

#include <assert.h> //for assert().
#include <stdio.h>
#include <stdlib.h>

typedef enum { DOT, LEFT, CENTER, RIGHT } Position;

const Position die[6] = { DOT, DOT, DOT, LEFT, CENTER, RIGHT };

#define SEED 4823

int promptNumberofPlayers(void) {
    int num_players = 3;
    printf("Number of players (3 to 10)? ");
    int scanf_result = scanf("%d", &num_players);

    if (scanf_result < 1 || num_players < 3 || num_players > 10) {
        fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
        num_players = 3;
    }

    return num_players;
}

unsigned promptSeed(void) {
    unsigned seed = 4823;
    printf("Random-number seed? ");
    int scanf_result = scanf("%u", &seed);

    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
        seed = SEED;
    }

    return seed;
}

void prng(unsigned seed) {
    srandom(seed);
}

int rollDice(void) {
    int ran = 0;

    ran = random() % 6;
    return ran;
}

void startingChips(int player_chips[], int num_players) {
    for (int i = 0; i < num_players; ++i) {
        player_chips[i] = 3;
    }
}

void turn(int player_chips[], int player_index, int num_players) {
    if (player_chips[player_index] > 0) {

        int maxTurns = player_chips[player_index] < 3 ? player_chips[player_index] : 3;

        for (int i = 0; (i < maxTurns) && (player_chips[player_index] > 0); ++i) {
            int roll = rollDice();

            switch (die[roll]) {
            case DOT: break;
            case LEFT:
                player_chips[player_index]--;
                player_chips[(player_index + num_players + 1) % num_players]++;
                break;
            case RIGHT:
                player_chips[player_index]--;
                player_chips[(player_index + num_players - 1) % num_players]++;
                break;
            case CENTER: player_chips[player_index]--; break;
            }
        }

        printf(
            "%s: ends her turn with %d\n", player_name[player_index], player_chips[player_index]);

    } else {
        return;
    }
}

int checkWinner(int player_chips[], int num_players) {
    int winner = -1;
    for (int i = 0; i < num_players; ++i) {
        if (player_chips[i] > 0) {
            if (winner == -1) {
                winner = i;
            } else {
                return -1;
            }
        }
    }
    return winner;
}

int main(void) {
    int num_players = promptNumberofPlayers();
    unsigned seed = promptSeed();
    prng(seed);

    int player_chips[num_players];
    startingChips(player_chips, num_players);

    while (checkWinner(player_chips, num_players) == -1) {
        for (int i = 0; i < num_players; ++i) {
            if (checkWinner(player_chips, num_players) == -1) {
                turn(player_chips, i, num_players);
            }
        }
    }

    int winner = checkWinner(player_chips, num_players);
    printf("%s won!\n", player_name[winner]);

    return 0;
}
