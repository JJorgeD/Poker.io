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

void pre_hands_scores(int *arr, int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int has_flush(Card *all, int n, Suit *flush_suit) {
    int count[4] = {0};
    for (int i=0; i<n; ++i) count[all[i].suit]++;
    for (int s=0; s<4; ++s)
        if (count[s] >= 5) {
            *flush_suit = s;
            return 1;
        }
    return 0;
}

int find_straight(int *ranks, int n, int *length, int *missing_cards[]) {
    int uniq[7], m=0;
    for (int i=0; i<n; ++i)
        if (i==0 || ranks[i]!=ranks[i-1]) uniq[m++] = ranks[i];
    int best = 0, best_start=0;
    for (int i=0; i<m; ++i) {
        int cnt = 1;
        int miss = 0;
        int last = uniq[i];
        for (int j=i+1; j<m && cnt<5; ++j) {
            if (uniq[j] == last+1) {
                cnt++; last = uniq[j];
            } else if (uniq[j] > last+1) {
                miss += (uniq[j] - last - 1);
                last = uniq[j];
                cnt++;
            }
        }
        if (cnt > best) { best=cnt; best_start=i; }
    }
    *length = best;
    if (5-best <= 2) {
        static int missing[2];
        int idx=0;
        int start = uniq[best_start];
        for (int k=0; k<5; ++k) {
            int target = start + k;
            bool found = false;
            for (int x=0; x<m; ++x)
                if (uniq[x]==target) { found=true; break; }
            if (!found && idx<2) missing[idx++] = target;
        }
        *missing_cards = missing;
    }

    return best >= 5;
}