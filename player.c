#include <stdio.h>
#include <string.h>
#include "player.h"

typedef struct PlayerNode {
    Player *player;
    struct PlayerNode *next;
} PlayerNode;

void init_player(Player *player, const char *name, int chips) {
    strncpy(player->name, name, MAX_NAME_LEN - 1);
    player->name[MAX_NAME_LEN - 1] = '\0';
    player->chips = chips;
    player->is_folded = 0;
}

void deal_to_player(Player *player, Card *deck, int *deck_pos) {
    for (int i = 0; i < HAND_SIZE; ++i) {
        player->hand[i] = deck[*deck_pos];
        (*deck_pos)++;
    }
}

void print_player_hand(Player *player) {
    printf("%s's hand: ", player->name);
    for (int i = 0; i < HAND_SIZE; ++i) {
        print_card(player->hand[i]);
        printf(" ");
    }
    printf("\n");
}

void fold_player(Player *player) {
    player->is_folded = 1;
}

PlayerNode* new_node(Player *p) {
    PlayerNode *n = malloc(sizeof *n);
    n->player = p;
    n->next = NULL;
    return n;
}

// Constrói lista circular
PlayerNode* build_circle(Player players[], int n) {
    PlayerNode *head = new_node(&players[0]);
    PlayerNode *prev = head;
    for (int i = 1; i < n; ++i) {
        PlayerNode *node = new_node(&players[i]);
        prev->next = node;
        prev = node;
    }
    prev->next = head;  // fecha o círculo
    return head;
}