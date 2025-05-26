#include "ranking.h"
#include <stdio.h>
#include <time.h>

void save_ranking(Player players[], int n) {
    FILE *f = fopen("ranking.txt", "a");
    time_t t = time(NULL);
    fprintf(f, "=== %s ===\n", ctime(&t));
    for (int i = 0; i < n; ++i)
        fprintf(f, "%s: %d fichas\n", players[i].name, players[i].chips);
    fprintf(f, "\n");
    fclose(f);
}
