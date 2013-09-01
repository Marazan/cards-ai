#ifndef H_BRISCOLA
#define
#include "cards.h"
#include<stdio.h>
#include<stdlib.h>

struct GameState;
typedef struct GameState GameState;

typedef struct Player Player;

struct Player
{
    int total_cards_in_hand;
    int empty_position;
    Card *cards[3];
    Card *(*take_turn)(GameState *state);
};

struct GameState 
{
    Deck *deck;
    int player_to_play;
    Card *played_card;
    Player *players[2];
    int scores[2];
};

struct FrozenGameState
{
    int deck_index;
    int p2empty;
    int p1empty;
    int p1cards[3];
    int p2cards[3];
    int scores[2];
};
#endif
