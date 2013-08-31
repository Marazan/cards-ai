#include "cards.h"
#include<stdio.h>
#include<stdlib.h>

struct GameState;

typedef Card *(*take_turn)(struct GameState *state);
typedef struct Player Player;
typedef struct GameState GameState;

struct Player
{
    int total_cards_in_hand;
    int empty_position;
    Card *cards[3];
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
    int scores[2]
}


void freeze_game_state(GameState *fromState, struct FrozenGameState *toState)
{
    toState->deck_index = fromState->deck->top_of_deck;
    toState->p1cards = memcpy();
    toState->p1empty = fromState->players[0].empty_position;
    toState->p21cards = memcpy();
    toState->p2empty = fromState->players[1].empty_position;
    toState->scores = memcpy();
}

GameState *create_game(Player *player1, Player*player2)
{
    GameState * state = (GameState *)malloc(sizeof(GameState));
    state->players[0] = player1;
    state->players[1] = player2;
    state->deck = create_deck();
    state->player_to_play = 0;
    return state;
}

int iterate_turn(GameState *state)
{
    return 1;
}
