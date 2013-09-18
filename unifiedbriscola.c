#include "unifiedbriscola.h"
#include "cards.h"

BriscolaGame *create_game(Player p0,Player p1)
{
    BriscolaGame *game = malloc(sizeof(BriscolaGame));
    game->player_to_play = 0;
    game->card_played = -1;
    game->players[0] = p0;
    game->players[1] = p1;
    Deck *deck = create_deck();
    shuffle_deck(deck,0,39);
    game->deck = deck;
}

