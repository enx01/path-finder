#ifndef PLAYER_H
#define PLAYER_H
#include "../structures.h"

/*
Initializes player_t structure and returns pointer to created structure.
(Don't forget to call method free_player).
*/ 
player_t *init_player();

/*
Handles player input and returns associated ACTION.
*/
ACTION handle_input(player_t *);


#endif // !PLAYER_H