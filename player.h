#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"

#define MAX_NAME_LEN 32
#define HAND_SIZE 2 // Texas Hold'em

typedef struct {
    char name[MAX_NAME_LEN];
    Card hand[HAND_SIZE];
    int chips;
    int is_folded; // 0 = jogando, 1 = desistiu
} Player;

void init_player(Player *player, const char *name, int chips);
void deal_to_player(Player *player, Card *deck, int *deck_pos);
void print_player_hand(Player *player);
void fold_player(Player *player);

#endif