#ifndef GAME_H
#define GAME_H
#include "../structures.h"

/*
Initializes game_t structure and returns pointer to created structure.
Default gamestate : MENU.
(Don't forget to call method free_game).
*/ 
game_t *init_game();

void run_game(game_t *, player_t *);

void free_game(game_t *);

#endif // !GAME_H