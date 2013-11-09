#ifndef H_BRISCOLA
#define H_BRISCOLA
#include "cards.h"
#include<stdio.h>
#include<stdlib.h>

struct GameState;
typedef struct GameState GameState;

struct Player;
typedef struct Player Player;

struct Player
{
    int total_cards_in_hand;
    int empty_position;
    int score;
    void * data;
    int mctp;
    Card *(*take_turn)(GameState *state, Player *player);
    Card *cards[3];
};


struct GameState 
{
    Deck *deck;
    int player_to_play;
    Card *played_card;
    Card *briscola;
    Player *players[2];
};

struct FrozenGameState
{
    int deck_index;
    int p2empty;
    int p1empty;
    Card *played_card;
    int player_to_play;
    Card *p1cards[3];
    Card *p2cards[3];
    int scores[2];
    Card *deck[40];
};

Card *first_card(GameState *state, Player *player);
Card *monte_carlo(GameState *state, Player *player);
Card *random_play(GameState *state, Player *player);
void freeze_game_state(GameState *fromState, struct FrozenGameState *toState);
void restore_game_state(struct FrozenGameState *fromState, GameState *toState);
GameState *create_game(Player *player1, Player *player2);
Player *create_player();
void score_card(Card *lead, Card *follow, int follower, GameState *state);
int compact_game(GameState *state);
int iterate_turn(GameState *state);
void print_game_state(GameState *state);
void reset_game(GameState *state);

#endif
