#include<cards.h>
#include<stdlib.h>
#include<stdio.h>

void display_card(Card *card)
{
    printf("%c%c",VALUE[card->value],SUIT[card->suit]);
}

void display_deck(Deck *deck)
{
    for (int i = 0; i < 40; i++)
    {
        display_card(i);
        printf(" ");
    }
    printf("\n");
}

void shuffle_deck(Deck *deck, int inclusive_start, int inclusive_end)
{
}

Card *take_top_card(Deck *deck)
{
}

Deck *create_deck()
{
}

