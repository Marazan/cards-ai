#include "briscola.h"
#include <string.h>

Card *random_play(GameState *state)
{
    printf("Randomly Playing Card");
    return NULL;
}

void freeze_game_state(GameState *fromState, struct FrozenGameState *toState)
{
    int int_in_bytes = sizeof(int);
    toState->deck_index = fromState->deck->top_of_deck;
    memcpy(toState->p1cards,fromState->players[0]->cards,3*int_in_bytes);
    toState->p1empty = fromState->players[0]->empty_position;
    memcpy(toState->p2cards,fromState->players[1]->cards,3*int_in_bytes);
    toState->p2empty = fromState->players[1]->empty_position;
    memcpy(toState->scores,fromState->scores,2*int_in_bytes);
}

GameState *create_game(Player *player1, Player *player2)
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
