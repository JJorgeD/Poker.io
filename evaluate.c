#include "evaluate.h"
#include <string.h>

HandScore evaluate_hand(Player *player, Game *game) {
    HandScore result;
    result.rank = HAND_HIGH_CARD;
    result.high_value = 0;

    int count[15] = {0}; // Ranks de 2 a 14 (ACE)

    for (int i = 0; i < HAND_SIZE; ++i)
        count[player->hand[i].rank]++;
    for (int i = 0; i < NUM_COMMUNITY_CARDS; ++i)
        count[game->community[i].rank]++;

    int pairs[2] = {0};
    int pair_index = 0;
    int three_kind = 0;

    for (int i = ACE; i >= TWO; --i) {
        if (count[i] == 3 && three_kind == 0) {
            three_kind = i;
        } else if (count[i] == 2 && pair_index < 2) {
            pairs[pair_index++] = i;
        }
    }

    if (three_kind) {
        result.rank = HAND_THREE_KIND;
        result.high_value = three_kind;
        return result;
    }

    if (pair_index == 2) {
        result.rank = HAND_TWO_PAIR;
        result.high_value = (pairs[0] > pairs[1]) ? pairs[0] : pairs[1];
        return result;
    }

    if (pair_index == 1) {
        result.rank = HAND_ONE_PAIR;
        result.high_value = pairs[0];
        return result;
    }

    // Carta mais alta
    for (int i = ACE; i >= TWO; --i) {
        if (count[i] > 0) {
            result.rank = HAND_HIGH_CARD;
            result.high_value = i;
            return result;
        }
    }

    return result;
}

int compare_hands(Player *p1, Player *p2, Game *game) {
    HandScore s1 = evaluate_hand(p1, game);
    HandScore s2 = evaluate_hand(p2, game);

    if (s1.rank > s2.rank)
        return 1;
    else if (s2.rank > s1.rank)
        return 2;
    else {
        if (s1.high_value > s2.high_value)
            return 1;
        else if (s2.high_value > s1.high_value)
            return 2;
        else
            return 0;
    }
}