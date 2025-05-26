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

#endif