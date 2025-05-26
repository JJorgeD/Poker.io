#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"

#define NUM_COMMUNITY_CARDS 5

typedef struct {
    Card community[NUM_COMMUNITY_CARDS];
    Player *players;
    int num_players;
    int pot;
} Game;

void init_game(Game *game, Player *players, int num_players);
void deal_community_cards(Game *game, Card *deck, int *deck_pos);
void print_community_cards(Game *game, int num_cards);

#endif