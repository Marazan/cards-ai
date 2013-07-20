#include "cards.h"

struct Player
{
    Card *cards[3];
}

struct GameState 
{
    Deck *deck;
    int player_to_play;
    Card *played_card;
    Player *players[2];
}
