#include <stdio.h>
#include "game.h"

void init_game(Game *game, Player *players, int num_players) {
    game->players = players;
    game->num_players = num_players;
    game->pot = 0;
    for (int i = 0; i < NUM_COMMUNITY_CARDS; ++i) {
        game->community[i].rank = 0;
        game->community[i].suit = 0;
    }
}

void deal_community_cards(Game *game, Card *deck, int *deck_pos) {
    // Flop
    for (int i = 0; i < 3; ++i) {
        game->community[i] = deck[(*deck_pos)++];
    }
    // Turn
    game->community[3] = deck[(*deck_pos)++];
    // River
    game->community[4] = deck[(*deck_pos)++];
}

void print_community_cards(Game *game, int num_cards) {
    printf("Cartas da mesa: ");
    for (int i = 0; i < num_cards; ++i) {
        print_card(game->community[i]);
        printf(" ");
    }
    printf("\n");
}