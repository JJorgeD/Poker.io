#ifndef EVALUATE_H
#define EVALUATE_H

#include "player.h"
#include "game.h"

typedef enum {
    HAND_HIGH_CARD = 1,
    HAND_ONE_PAIR,
    HAND_TWO_PAIR,
    HAND_THREE_KIND
} HandRank;

typedef struct {
    HandRank rank;
    int high_value; // para desempate
} HandScore;

HandScore evaluate_hand(Player *player, Game *game);
int compare_hands(Player *p1, Player *p2, Game *game);
void pre_hands_scores(int *arr, int n);
int has_flush(Card *all, int n, Suit *flush_suit);
int find_straight(int *ranks, int n, int *length, int **missing_cards);

#endif