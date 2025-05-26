#include <stdio.h>
#include <string.h>
#include "betting.h"

void player_turn(Player *player, Game *game, int *current_bet) {
    if (player->chips <= 0 || player->is_folded) return;

    printf("\n%s, você tem %d fichas. Aposta atual: %d. Ações: [c]all, [r]aise, [f]old: ", 
        player->name, player->chips, *current_bet);

    char action[10];
    scanf("%s", action);

    if (strcmp(action, "f") == 0) {
        fold_player(player);
        printf("%s desistiu!\n", player->name);
    } else if (strcmp(action, "r") == 0) {
        int raise;
        printf("Quanto deseja aumentar? ");
        scanf("%d", &raise);
        if (raise > 0 && raise <= player->chips) {
            *current_bet += raise;
            player->chips -= *current_bet;
            game->pot += *current_bet;
            printf("%s aumentou para %d.\n", player->name, *current_bet);
        } else {
            printf("Aposta inválida.\n");
            fold_player(player);
        }
    } else {
        int to_call = *current_bet;
        if (player->chips < to_call) to_call = player->chips;
        player->chips -= to_call;
        game->pot += to_call;
        printf("%s pagou %d.\n", player->name, to_call);
    }
}

void bot_turn(Player *bot, Game *game, int *current_bet) {
    if (bot->chips <= 0 || bot->is_folded) return;

    int to_call = *current_bet;
    if (to_call > bot->chips) {
        fold_player(bot);
        printf("%s (bot) desistiu.\n", bot->name);
    } else {
        bot->chips -= to_call;
        game->pot += to_call;
        printf("%s (bot) pagou %d.\n", bot->name, to_call);
    }
}