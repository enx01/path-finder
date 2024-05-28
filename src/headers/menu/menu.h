#ifndef MENU_H
#define MENU_H
#include "../structures.h"

menu_t *init_menu();

game_t *run_menu(menu_t *, player_t *);


void update_cursor(menu_t *, ACTION);
void render_menu(menu_t *, player_t *);

#endif // !MENU_H