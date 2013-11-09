#include "briscola.h"
#include "cards.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int MONTE_ITERS = 1000;

Card *play_card(Player *player, int index)
{
    Card *card = player->cards[index];
    player->empty_position = index;
    player->cards[index] = NULL;
    return card;
}
Card *random_play(GameState *state,Player *player)
{
    //if (player == state->players[1]) printf("Randomly Playing Card\n");
    Card *card;
    int index;
    do{
        index = random_range(0,2);
        card = player->cards[index];
    } while (card == NULL);

    card = play_card(player,index);
    return card;
}

Card *play_then_random(GameState *state, Player *player)
{
    //printf("Playing Selected");
    //display_card(player->cards[player->mctp]);
    //printf("\n");
    Card *card;
    card = play_card(player,player->mctp);
    player->take_turn = &random_play; 
    player->mctp = -10000;
    return card;
}

void star_list(Player *player, int card_index)
{
    for (int cc = 0; cc < 3; cc++)
    {
        if (cc == card_index) printf("*");
        display_card(player->cards[cc]);
        if (cc == card_index) printf("*");
        printf("\n");
    }
 
}

Card *monte_carlo(GameState *state, Player *player)
{
    int insert_card_at;
    int top;
    int wins[3] = {-2,-2,-2};
    struct FrozenGameState *fgs = (struct FrozenGameState *)player->data;
    Player *other_player = state->players[1];
    top = state->deck->top_of_deck;
    if (state->deck->top_of_deck > 0)
    {
        top = compact_game(state) - 1;
    }
    freeze_game_state(state,fgs);

    for (int card_index = 0; card_index < 3; card_index ++)
    {
        restore_game_state(fgs,state);
        if (player->cards[card_index] == NULL) continue;
        wins[card_index] = 0;
        for (int its = 0; its < MONTE_ITERS; its ++)
        {
            restore_game_state(fgs,state);
            player->mctp = card_index;
            player->take_turn = &play_then_random;
            if (state->deck->top_of_deck > 0) 
            {
                shuffle_deck(state->deck,1,top-1);
                insert_card_at = 0;
                while (top > state->deck->top_of_deck)
                {
                    while (other_player->cards[insert_card_at]==NULL)
                    {
                        insert_card_at += 1;
                    }
                    other_player->cards[insert_card_at] = state->deck->cards[top];
                    top -= 1;
                    insert_card_at+=1;
                }
            }
            int status = -1;
            while (status == -1 || status == -2)
            {
                status = iterate_turn(state);
            }
            if (status == 0)
            {
                wins[card_index] += 1;
            }
        }
    }
    restore_game_state(fgs,state);
    player->take_turn = &monte_carlo;
    int max = wins[0];
    int index = 0;
    for (int k = 1; k < 3; k ++)
    {
        if (wins[k] > max)
        {
            max = wins[k];
            index = k;
        }
    }
    Card *card = play_card(player,index);
    return card;
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

Card* card(Deck *deck, int index)
{
    return deck->cards[index];
}

void freeze_game_state(GameState *fromState, struct FrozenGameState *toState)
{
    int int_in_bytes = sizeof(int);
    int card_in_bytes= sizeof(Card *);
    toState->deck_index = fromState->deck->top_of_deck;
    memcpy(toState->deck,fromState->deck->cards,40*card_in_bytes);
    memcpy(toState->p1cards,fromState->players[0]->cards,3*int_in_bytes);
    toState->p1empty = fromState->players[0]->empty_position;
    memcpy(toState->p2cards,fromState->players[1]->cards,3*int_in_bytes);
    toState->p2empty = fromState->players[1]->empty_position;
    toState->scores[0] = fromState->players[0]->score;
    toState->scores[1] = fromState->players[1]->score;
    toState->played_card = fromState->played_card;
    toState->player_to_play = fromState->player_to_play;
}

void restore_game_state(struct FrozenGameState *fromState, GameState *toState)
{
    int int_in_bytes = sizeof(int);
    int card_in_bytes= sizeof(Card *);
    toState->deck->top_of_deck = fromState->deck_index;
    memcpy(toState->deck->cards,fromState->deck,40*card_in_bytes);
    memcpy(toState->players[0]->cards,fromState->p1cards,3*int_in_bytes);
    toState->players[0]->empty_position=fromState->p1empty; 
    memcpy(toState->players[1]->cards,fromState->p2cards,3*int_in_bytes);
    toState->players[1]->empty_position = fromState->p2empty;
    toState->players[0]->score = fromState->scores[0];
    toState->players[1]->score = fromState->scores[1];
    toState->played_card = fromState->played_card;
    toState->player_to_play = fromState->player_to_play;

}

int compact_game(GameState *state)
{
    Card *temp;
    int insert_point;
    insert_point = state->deck->top_of_deck + 1;
    //Starting from top of deck +1
    //loop through other player cards and move them to top of deck
    for (int i =0; i < 3; i++)
    {
        if (state->players[1]->cards[i] == NULL) continue;
        for (int j = insert_point; j < 40; j++)
        {
            if (state->players[1]->cards[i] == state->deck->cards[j])
            {
                temp = state->deck->cards[j];
                state->deck->cards[j]=state->deck->cards[insert_point];
                state->deck->cards[insert_point] = temp;
            }
        }
        insert_point += 1;
    }
    return insert_point;
}
void deal_cards_to_players(GameState *state)
{
    for (int p = 0; p < 2; p++)
    {
        for (int i = 0; i < 3; i++)
        {
            state->players[p]->cards[i] = take_top_card(state->deck);
        }
    }
}

GameState *create_game(Player *player1, Player *player2)
{
    GameState *state = (GameState *)malloc(sizeof(GameState));
    state->players[0] = player1;
    state->players[1] = player2;
    state->deck = create_deck();
    shuffle_deck(state->deck,0,39);
    state->player_to_play = 0;
    state->briscola = state->deck->cards[0];
    deal_cards_to_players(state);
    state->played_card = NULL;
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
        printf("HORRIBLE ERROR");
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
    printf("Monte Player %d\n",state->players[0]->mctp);
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

void reset_game(GameState *state)
{
    shuffle_deck(state->deck,0,39);
    state->deck->top_of_deck = 39;
    state->player_to_play = 0;
    deal_cards_to_players(state);
    state->players[0]->score = 0;
    state->players[1]->score = 0;
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
