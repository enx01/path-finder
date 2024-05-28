#include "../headers/game/game.h"
#include "../headers/game/player.h"

game_t *init_game()
{
    game_t *res = malloc(sizeof(game_t));

    res->state = MENU;

    res->current = NULL;

    res->running = 0;
    
    return res;
}

void run_game(game_t *g, player_t *p)
{
    g->running = 1;

    ACTION a;
    while(g->running) 
    {
        a = handle_input(p);

        switch (g->state)
        {
        case MENU:
            
            

            break;
        
        default:
            break;
        }
    }
}

void free_game(game_t *g)
{
    // TODO : Free current tree

    free(g);
}