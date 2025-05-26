#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "player.h"
#include "game.h"
#include "evaluate.h"
#include "betting.h"
#include "ranking.h"

#define NUM_PLAYERS 2
#define START_CHIPS 1000
#define INITIAL_BET 50

int main() {
    Card deck[NUM_CARDS];
    Player players[NUM_PLAYERS];
    PlayerNode *dealer;
    Game game;
    int deck_pos;

    srand((unsigned)time(NULL));

    init_player(&players[0], "Você", START_CHIPS);
    init_player(&players[1], "Bot", START_CHIPS);

    dealer = build_circle(players, NUM_PLAYERS);
    init_game(&game, players, NUM_PLAYERS);

    while (quantos_com_chips(dealer) > 1) {

        deck_pos = 0;
        init_deck(deck);
        shuffle_deck(deck);
        game.pot = 0;


        PlayerNode *p = dealer->next;
        do {
            p->player->is_folded = 0;
            p = p->next;
        } while (p != dealer->next);


        p = dealer->next;
        do {
            deal_to_player(p->player, deck, &deck_pos);
            print_player_hand(p->player);
            p = p->next;
        } while (p != dealer->next);


        int current_bet = INITIAL_BET;
        printf("\n💰 Rodada de apostas (pré-flop)\n");
        betting_round(dealer->next, &game, &current_bet);


        deal_flop(&game, deck, &deck_pos);
        printf("\n🃏 Flop:\n");
        print_community_cards(&game, 3);
        current_bet = 0;
        betting_round(dealer->next, &game, &current_bet);


        deal_turn(&game, deck, &deck_pos);
        printf("\n🃏 Turn:\n");
        print_community_cards(&game, 4);
        current_bet = 0;
        betting_round(dealer->next, &game, &current_bet);


        deal_river(&game, deck, &deck_pos);
        printf("\n🃏 River:\n");
        print_community_cards(&game, 5);
        current_bet = 0;
        betting_round(dealer->next, &game, &current_bet);


        printf("\n🏁 Showdown\n");
        PlayerNode *winner = NULL;

        int active_count = 0;
        p = dealer->next;
        do {
            if (!p->player->is_folded) {
                if (winner == NULL) winner = p;
                active_count++;
            }
            p = p->next;
        } while (p != dealer->next);

        if (active_count == 1) {
            printf("🏆 %s venceu porque o oponente desistiu!\n",
                   winner->player->name);
        } else {


            p = dealer->next;
            do {
                if (!p->player->is_folded && p != winner) {
                    int res = compare_hands(p->player, winner->player, &game);
                    if (res == 1) winner = p;
                }
                p = p->next;
            } while (p != dealer->next);
            printf("🏆 Vencedor: %s com a melhor mão!\n", winner->player->name);
        }

        printf("💰 Pote final: %d fichas\n\n", game.pot);
        winner->player->chips += game.pot;


        save_ranking(players, NUM_PLAYERS);


        printf("💳 Fichas restantes:\n");
        for (int i = 0; i < NUM_PLAYERS; ++i) {
            printf("  %s: %d\n", players[i].name, players[i].chips);
        }
        printf("\n---------------------------------------\n\n");


        dealer = dealer->next;
    }

    printf("🎉 Fim do jogo! Obrigado por jogar.\n");
    return 0;
}
