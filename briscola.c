#include "briscola.h"
#include <string.h>

Card *random_play(GameState *state)
{
    printf("Randomly Playing Card\n");
    return NULL;
}

Card *first_card(GameState *state, Player *player)
{
    Card *card_to_play;
    for (int i = 0; i <3; i++)
    {
        if (player->cards[i] != NULL)
        {
            card_to_play = player->cards[i];
            player->empty_position  = i;
            player->cards[i] = NULL;
            break;
        }
    }
    return card_to_play;
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

void restore_game_state(struct FrozenGameState *fromState, GameState *toState)
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
    state->briscola = state->deck->cards[0];
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

void score_card(Card *lead, Card *follow, int follower, GameState *state)
{
    /*printf("Lead ");
    display_card(lead);
    printf("\nFollowed ");
    display_card(follow);
    printf("\n");*/
    int victor = follower;
    int briscola_suit = state->briscola->suit; 
    int score = POINTS[lead->value] + POINTS[follow->value];

    if (follow->suit == briscola_suit && lead->suit != briscola_suit)
    {
        //Follower wins
    }
    else if (follow->suit != briscola_suit && lead->suit == briscola_suit)
    {
        //Leader wins
        victor = (victor + 1)%2;
    }
    else if (follow->suit != lead->suit)
    {
        //Leader wins
        victor = (victor + 1)%2;
    }
    else if (follow->value > lead->value)
    {
    }
    else if (follow->value < lead->value)
    {
        //Leader wins
        victor = (victor + 1)%2;
    }
    else
    {
        exit(-1);
    }
    state->players[victor]->score += score;
    state->played_card = NULL;
    state->player_to_play = victor;
}

void print_game_state(GameState *state)
{
    display_deck(state->deck);
    printf("Top of Deck %d\n",state->deck->top_of_deck);
    printf("Scores [%d,%d]\n",state->players[0]->score,state->players[1]->score);
    for (int j = 0; j<2;j++)
    {
        printf("Player %d ",j);
        for (int i =0; i < 3; i++)
        {
            display_card(state->players[j]->cards[i]);
        }
        printf("\n");
    }
}

void refresh_players_cards(GameState *state)
{
    int player_to_take = state->player_to_play;
    if (state->deck->top_of_deck > 0)
    {
        state->players[player_to_take]->cards[state->players[player_to_take]->empty_position] = take_top_card(state->deck);
        player_to_take = (player_to_take +1)%2;
        state->players[player_to_take]->cards[state->players[player_to_take]->empty_position] = take_top_card(state->deck);
    }
}
int iterate_turn(GameState *state)
{
    Card *card_played = state->
        players[state->player_to_play]->
            take_turn(state,state->players[state->player_to_play]);
    if (state->played_card == NULL)
    {
        state->played_card = card_played;
        state->player_to_play += 1;
        state->player_to_play %= 2;
    }
    else
    {
        score_card(state->played_card, card_played, state->player_to_play,state);
        refresh_players_cards(state);
    }

    if (state->played_card != NULL)
    {
        return -2;
    }
    else if (state->players[0]->score > 60)
    {
        return 0;
    }
    else if (state->players[1]->score > 60)
    {
        return 1;
    }
    else if (state->players[0]->score == 60 && state->players[1]->score == 60 )
    {
        return -3;
    }
    else
    {
        return -1;
    }
}
