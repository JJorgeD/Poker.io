#include <stdio.h>
#include "deck.h"
#include "player.h"
#include "game.h"
#include "evaluate.h"
#include "betting.h"
#include "ia_api.h" // se estiver usando a simulação de IA

int main() {
    // Cria e embaralha o baralho
    Card deck[NUM_CARDS];
    init_deck(deck);
    shuffle_deck(deck);

    // Cria dois jogadores: você e o bot
    Player players[2];
    init_player(&players[0], "Você", 1000);
    init_player(&players[1], "Bot", 1000);

    // Posição atual no baralho (controle da distribuição)
    int deck_pos = 0;

    // Distribui 2 cartas da mão para cada jogador
    for (int i = 0; i < 2; ++i) {
        deal_to_player(&players[i], deck, &deck_pos);
        print_player_hand(&players[i]);
    }

    // Cria a estrutura do jogo e associa os jogadores
    Game game;
    init_game(&game, players, 2);
    deal_community_cards(&game, deck, &deck_pos); // flop + turn + river

    // Inicia uma rodada de apostas (pré-flop)
    int current_bet = 50; // aposta inicial
    printf("\n💰 Rodada de apostas (pré-flop)\n");
    player_turn(&players[0], &game, &current_bet); // Jogador humano
    bot_turn(&players[1], &game, &current_bet);    // Bot IA ou simulado

    // Mostra o flop
    printf("\n🃏 Flop:\n");
    print_community_cards(&game, 3);

    // Mostra o turn
    printf("\n🃏 Turn:\n");
    print_community_cards(&game, 4);

    // Mostra o river
    printf("\n🃏 River:\n");
    print_community_cards(&game, 5);

    // Avalia quem venceu a rodada
    printf("\n🏁 Determinando o vencedor...\n");
    printf("\n💵 Pot final: %d fichas\n", game.pot);

    // Verifica se alguém desistiu (fold)
    if (players[0].is_folded && !players[1].is_folded) {
        printf("🏆 %s venceu porque %s desistiu!\n", players[1].name, players[0].name);
        players[1].chips += game.pot;
    } else if (players[1].is_folded && !players[0].is_folded) {
        printf("🏆 %s venceu porque %s desistiu!\n", players[0].name, players[1].name);
        players[0].chips += game.pot;
    } else {
        // Compara as mãos e determina o vencedor
        int result = compare_hands(&players[0], &players[1], &game);
        if (result == 1) {
            printf("🏆 %s venceu!\n", players[0].name);
            players[0].chips += game.pot;
        } else if (result == 2) {
            printf("🏆 %s venceu!\n", players[1].name);
            players[1].chips += game.pot;
        } else {
            printf("🤝 Empate! Pot dividido.\n");
            players[0].chips += game.pot / 2;
            players[1].chips += game.pot / 2;
        }
    }

    // Mostra fichas restantes
    printf("\n💳 Fichas restantes:\n");
    printf("%s: %d fichas\n", players[0].name, players[0].chips);
    printf("%s: %d fichas\n", players[1].name, players[1].chips);

    return 0;
}