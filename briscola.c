#include "briscola.h"
#include <string.h>

Card *random_play(GameState *state)
{
    printf("Randomly Playing Card\n");
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
    toState->scores[0] = fromState->players[0]->score;
    toState->scores[1] = fromState->players[1]->score;
    toState->played_card = fromState->played_card;
}

void restore_ganme_state(struct FrozenGameState *fromState, GameState *toState)
{
}

GameState *create_game(Player *player1, Player *player2)
{
    GameState *state = (GameState *)malloc(sizeof(GameState));
    state->players[0] = player1;
    state->players[1] = player2;
    state->deck = create_deck();
    shuffle_deck(state->deck,0,39);
    state->player_to_play = 0;
    for (int p = 0; p < 2; p++)
    {
        for (int i = 0; i < 3; i++)
        {
            state->players[p]->cards[i] = take_top_card(state->deck);
        }
    }
    return state;
}

Player *create_player()
{
    Player *player = (Player *)malloc(sizeof(Player));
    player->total_cards_in_hand = 3;
    player->empty_position = -1;
    player->score = 0;

    return player;
}

int iterate_turn(GameState *state)
{
    return 1;
}
