#include "../headers/game/game.h"
#include "../headers/game/player.h"
#include "../headers/tree/directory.h"

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

    g->current = generate_directory(2, 5);

    fprintf(stderr, "number of elements in tree : %d\n", nb_elements_in_dir(g->current));

    ACTION a;
    while(g->running) 
    {
        a = handle_input(p);

        render_game(g, p);

        nanosleep(&ts, NULL);
    }
}

void render_game(game_t *g, player_t *p)
{
    // Borders
    for (int x = 0; x < GAME_WIDTH; x++) {
        mvaddch(0, x, '-');
        mvaddch(GAME_HEIGHT-2, x, '-');
    }
    for (int y = 0; y < GAME_HEIGHT-1; y++) {
        mvaddch(y, 0, '|');
        mvaddch(y, GAME_WIDTH-1, '|');
    }
    mvaddch(0, 0,'o');
    mvaddch(0, GAME_WIDTH-1,'o');
    mvaddch(GAME_HEIGHT-2, 0,'o');
    mvaddch(GAME_HEIGHT-2, GAME_WIDTH-1,'o');   

    for (int i = 1; i < GAME_WIDTH-1; i++)
    {
        for (int j = 1; j < GAME_HEIGHT-2; ++j)
        {
            mvaddch(j, i, ' ');
        }
    }

    // render_word

    int row = 1;
    render_directory(g->current);
    // end_program();

    attron(COLOR_PAIR(1)); // Enable custom color 1
    attron(A_BOLD); // Enable bold
    mvaddch(GAME_HEIGHT-1, 0, '$');
    for (int x = 0; x < GAME_WIDTH; x++) {
        if (x >= INPUT_MAX || x >= p->cursor)
            mvaddch(GAME_HEIGHT-1, x+1, ' ');
        else
            mvaddch(GAME_HEIGHT-1, x+1, p->data[x]);
    }
    attroff(A_BOLD); // Disable bold
    attroff(COLOR_PAIR(1)); // Disable custom color 1
    
    refresh(); // Apply the changes to the terminal
}

void free_game(game_t *g)
{
    if (g->current != NULL)
    {
        free_directory(g->current);
    }

    free(g);
}