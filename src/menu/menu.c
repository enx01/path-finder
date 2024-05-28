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

    mvprintw(1, 10, "Path-finder");
    mvprintw(3, 6, "Choose difficulty :");

    for (int i = 1; i < 29; i++)
    {
        mvaddch(6, i, ' ');
        mvaddch(7, i, ' ');
        mvaddch(8, i, ' ');
    }
    
    switch (m->difficulty_cursor)
    {
    case 0:
        mvprintw(6, 11, "> Easy <");
        mvprintw(7, 12, "Normal");
        mvprintw(8, 13, "Hard");
        break;
    case 1:
        mvprintw(6, 13, "Easy");
        mvprintw(7, 10, "> Normal <");
        mvprintw(8, 13, "Hard");
        break;
    case 2:
        mvprintw(6, 13, "Easy");
        mvprintw(7, 12, "Normal");
        mvprintw(8, 11, "> Hard <");
        break;
    default:
        break;
    }
    

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