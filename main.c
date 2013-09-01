#include "cards.h"
#include "briscola.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

void main()
{
        srand(time(NULL));
        Deck *deck = create_deck();
        shuffle_deck(deck,0,39);
        display_card(deck->cards[deck->top_of_deck]);
        printf("\n");
        Player *p = (Player *)malloc(sizeof(Player));
        p->take_turn=&random_play;
        p->take_turn(NULL);
}

