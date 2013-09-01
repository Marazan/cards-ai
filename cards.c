#include "cards.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

char SUIT[4] = {'H','C','S','D'};
char VALUE[10] = {'2','4','5','6','7','J','Q','K','3','A'};
int POINTS[10] = {0,0,0,0,0,2,3,4,10,11};


void display_card(Card *card)
{
    printf("%c%c",VALUE[card->value],SUIT[card->suit]);
}

void display_deck(Deck *deck)
{
    for (int i = 0; i < 40; i++)
    {
        display_card(deck->cards[i]);
        printf(" ");
    }
    printf("\n");
}

int random_range(int min, int max)
{
    int r;
    max = max+1;
    const int range = max - min;
    const int buckets = RAND_MAX / range;
    const int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);

}

void shuffle_deck(Deck *deck, int inclusive_start, int inclusive_end)
{
    int newLocation;
    Card *tmp;
    for (int i = inclusive_start; i <= inclusive_end; i++)
    {
        newLocation = random_range(i,inclusive_end);
        tmp = deck->cards[i];
        deck->cards[i] = deck->cards[newLocation];
        deck->cards[newLocation] = tmp;
    }
}

Card *take_top_card(Deck *deck)
{
    int top = deck->top_of_deck;
    deck->top_of_deck --;
    return deck->cards[top];
}

Deck *create_deck()
{
    Deck *deck = (Deck *)(malloc(sizeof(Deck)));
    for (int suit = 0; suit < 4; suit ++)
    {
        for (int value = 0; value < 10; value ++)
        {
            deck->cards[suit*10+value] = (Card *)(malloc(sizeof(Card)));
            deck->cards[suit*10+value]->suit = suit; 
            deck->cards[suit*10+value]->value = value; 
            deck->cards[suit*10+value]->score = POINTS[value]; 
        }
    }
    return deck;
}

