CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJS = main.o deck.o player.o game.o evaluate.o betting.o
LDLIBS = -lcurl


poker: $(OBJS)
	$(CC) $(CFLAGS) -o poker $(OBJS)

main.o: main.c deck.h player.h game.h evaluate.h betting.h
deck.o: deck.c deck.h
player.o: player.c player.h deck.h
game.o: game.c game.h player.h deck.h
evaluate.o: evaluate.c evaluate.h player.h game.h
betting.o: betting.c betting.h game.h player.h
ranking.o: ranking.c ranking.h player.h

clean:
	rm -f *.o poker

