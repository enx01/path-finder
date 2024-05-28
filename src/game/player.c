#include "../headers/game/player.h"

player_t *init_player()
{
    player_t * res = malloc(sizeof(player_t));

    res->score = 0;

    return res;
}

ACTION handle_input(player_t *p)
{
    int c,
        prev_c = ERR;
    while ( (c = getch()) != ERR )
    {
        if (prev_c != ERR && prev_c != c) {
            ungetch(c); // put 'c' back in the queue
            break;
        }
        prev_c = c;
    }
    ACTION a;
    switch (prev_c) {
        case ERR: break;
        case KEY_LEFT:
            a = LEFT_MENU_CTRL; 
            break;
        case KEY_RIGHT:
            a = RIGHT_MENU_CTRL;
            break;
        case KEY_UP:
            a = UP_MENU_CTRL; 
            break;
        case KEY_DOWN:
            a = DOWN_MENU_CTRL; 
            break;
        case '~':
            a = QUIT; 
            end_program();
            break;
        case KEY_BACKSPACE:
            if (p->cursor > 0) p->cursor--;
            break;
        case ' ':
            a = OK_MENU;
            break;
        case '\r':
            a = COMPUTE; 
            p->data[p->cursor] = '\0';
            break;
        default:
            if (prev_c >= ' ' && prev_c <= '~' && p->cursor < INPUT_MAX)
                p->data[(p->cursor)++] = prev_c;
            break;
    }
    return a;


}