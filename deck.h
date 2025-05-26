#ifndef DECK_H
#define DECK_H

#define NUM_CARDS 52

typedef enum { HEARTS, DIAMONDS, CLUBS, SPADES } Suit;
typedef enum {
    TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN,
    EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE
} Rank;

typedef struct {
    Suit suit;
    Rank rank;
} Card;

void init_deck(Card *deck);
void shuffle_deck(Card *deck);
void print_card(Card card);

#endif