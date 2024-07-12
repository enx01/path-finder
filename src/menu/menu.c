#include "../headers/menu/menu.h"
#include "../headers/game/player.h"

menu_t *init_menu()
{
    menu_t *res = malloc(sizeof(menu_t));

    res->difficulty_cursor = 0;

    return res;
}

game_t *run_menu(menu_t *m, player_t *p)
{
    game_t *g = malloc(sizeof(game_t));

    ACTION a = DOWN_MENU_CTRL;
    update_cursor(m, a);

    while (a != OK_MENU)
    {
        a = handle_input(p);

        update_cursor(m, a);

        render_menu(m, p);
        
        nanosleep(&ts, NULL);
    }

    g = malloc(sizeof(game_t));

    g->difficulty = m->difficulty_cursor;

    g->current = NULL;
}

void update_cursor(menu_t *m, ACTION a)
{
    int new;

    switch (a)
    {
    case DOWN_MENU_CTRL:
        new = (m->difficulty_cursor + 1);
        break;
    case UP_MENU_CTRL:
        new = (m->difficulty_cursor - 1);
        break;
    default:
        new = m->difficulty_cursor;
        break;
    }

    if (new > 2)
    {
        m->difficulty_cursor = 0;
    }
    else if (new < 0) {
        m->difficulty_cursor = 2;
    }
    else
    {
        m->difficulty_cursor = new;
    }
}

void render_menu(menu_t *m, player_t *p)
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

    char *buf = malloc(GAME_WIDTH);

    strcpy(buf, "Path-finder");

    mvprintw(1, (GAME_WIDTH/2) - strlen(buf)/2, buf);

    strcpy(buf, "Choose difficulty :");

    mvprintw(3, (GAME_WIDTH/2) - strlen(buf)/2, buf);


    
    
    switch (m->difficulty_cursor)
    {
    case 0:

        for (int i = 1; i < GAME_WIDTH-1; i++)
        {
            mvaddch(6, i, ' ');
            mvaddch(7, i, ' ');
            mvaddch(8, i, ' ');
        }

        strcpy(buf, "> Easy <");
        mvprintw(6, (GAME_WIDTH/2) - strlen(buf)/2, buf);
        
        strcpy(buf, "Normal");
        mvprintw(7, (GAME_WIDTH/2) - strlen(buf)/2, buf);

        strcpy(buf, "Hard");
        mvprintw(8, (GAME_WIDTH/2) - strlen(buf)/2, buf);
        break;
    case 1:
        for (int i = 1; i < GAME_WIDTH-1; i++)
        {
            mvaddch(6, i, ' ');
            mvaddch(7, i, ' ');
            mvaddch(8, i, ' ');
        }

        strcpy(buf, "Easy");
        mvprintw(6, (GAME_WIDTH/2) - strlen(buf)/2, buf);
        
        strcpy(buf, "> Normal <");
        mvprintw(7, (GAME_WIDTH/2) - strlen(buf)/2, buf);

        strcpy(buf, "Hard");
        mvprintw(8, (GAME_WIDTH/2) - strlen(buf)/2, buf);
        break;
    case 2:
        for (int i = 1; i < GAME_WIDTH-1; i++)
        {
            mvaddch(6, i, ' ');
            mvaddch(7, i, ' ');
            mvaddch(8, i, ' ');
        }

        strcpy(buf, "Easy");
        mvprintw(6, (GAME_WIDTH/2) - strlen(buf)/2, buf);
        
        strcpy(buf, "Normal");
        mvprintw(7, (GAME_WIDTH/2) - strlen(buf)/2, buf);

        strcpy(buf, "> Hard <");
        mvprintw(8, (GAME_WIDTH/2) - strlen(buf)/2, buf);
        break;
    default:
        for (int i = 1; i < GAME_WIDTH-1; i++)
        {
            mvaddch(6, i, ' ');
            mvaddch(7, i, ' ');
            mvaddch(8, i, ' ');
        }
        break;
    }
        
    free(buf);

    // attron(COLOR_PAIR(1)); // Enable custom color 1
    // attron(A_BOLD); // Enable bold
    // mvaddch(GAME_HEIGHT-1, 0, '$');
    // for (int x = 0; x < GAME_WIDTH; x++) {
    //     if (x >= INPUT_MAX || x >= p->cursor)
    //         mvaddch(GAME_HEIGHT-1, x+1, ' ');
    //     else
    //         mvaddch(GAME_HEIGHT-1, x+1, p->data[x]);
    // }
    // attroff(A_BOLD); // Disable bold
    // attroff(COLOR_PAIR(1)); // Disable custom color 1
    
    refresh(); // Apply the changes to the terminal
}