#ifndef H_UNIFIED_BRISCOLA
#define H_UNIFIED_BRISCOLA

#include "cards.h"

struct _BriscolaGame;
typedef struct _BriscolaGame BriscolaGame;
struct _Player;
typedef struct _Player Player;


struct _Player
{
    Card *(*take_turn)(BriscolaGame *state, Player *player, int index);
    void *data;
};

struct _BriscolaGame
{
    int player_to_play;
    int card_played;
    Card *briscola;
    Player *players[2];
    int played_position;
    Deck *deck[40];
};

struct _FrozenState
{

}

BriscolaGame *create_game(Player *p0,Player *p1);
/* Return Values are 
 * 0 Player 0 has won
 * 1 Player 1 has won
 * -1 A Draw
 * -2 Game Continues
 */
int iterate_turn(BriscolaGame *game);
#endif
