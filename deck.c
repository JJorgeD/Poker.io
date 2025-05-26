#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"

void init_deck(Card *deck) {
    int i = 0;
    for (int s = 0; s < 4; ++s) {
        for (int r = TWO; r <= ACE; ++r) {
            deck[i].suit = s;
            deck[i].rank = r;
            i++;
        }
    }
}

void shuffle_deck(Card *deck) {
    srand(time(NULL));
    for (int i = NUM_CARDS - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void print_card(Card card) {
    const char *ranks[] = {
        "", "", "2", "3", "4", "5", "6", "7",
        "8", "9", "10", "J", "Q", "K", "A"
    };
    const char *suits[] = { "♥", "♦", "♣", "♠" };
    printf("%s%s", ranks[card.rank], suits[card.suit]);
}