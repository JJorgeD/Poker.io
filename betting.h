#ifndef BETTING_H
#define BETTING_H

#include "game.h"

void player_turn(Player *player, Game *game, int *current_bet);
void bot_turn(Player *bot, Game *game, int *current_bet);

#endif