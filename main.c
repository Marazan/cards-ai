#include "cards.h"
#include "briscola.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

void main()
{
        srand(time(NULL));
        Player *p1 = create_player();
        p1->take_turn = &first_card;
        Player *p2 = create_player();
        p2->take_turn = &first_card;
        GameState *state = create_game(p1,p2);
        struct FrozenGameState *fgs = malloc(sizeof(struct FrozenGameState));
        freeze_game_state(state,fgs);
        printf("\n");
        for (int gn = 0;gn < 200000; gn++)
        {
            //print_game_state(state);
            int status = -1;
            int i = 0;
            while (status == -1 || status == -2)
            {
                //printf("Turn %d\n",i);
                status = iterate_turn(state);
                //print_game_state(state);
                //printf("\n");
                i += 1;
            }

            //print_game_state(state);
            //printf("Victory for player %d\n\n",status);
            restore_game_state(fgs,state);
            //reset_game(state);
        }
}

