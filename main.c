#include "cards.h"
#include "briscola.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

void main()
{
        srand(time(NULL));
        Player *p1 = create_player();
        Player *p2 = create_player();
        GameState *state = create_game(p1,p2);
        display_deck(state->deck);
        for (int i =0; i < 3; i++)
        {
            printf("*\n");
            display_card(state->players[0]->cards[i]);
        }
        printf("\n");
}

