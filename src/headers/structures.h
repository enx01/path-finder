#ifndef STRUCTURES_H
#define STRUCTURES_H
#define INPUT_MAX 255
#define GAME_WIDTH 30
#define GAME_HEIGHT 15

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

typedef enum GAMESTATE {MENU, IN_GAME} GAMESTATE;
typedef enum ACTION {
    UP_MENU_CTRL, DOWN_MENU_CTRL,
    LEFT_MENU_CTRL, RIGHT_MENU_CTRL,
    OK_MENU, COMPUTE, QUIT
} ACTION;

struct file_t
{
    char name[10];
};
typedef struct file_t file_t;

typedef struct directory_t directory_t;
struct directory_t
{
    file_t **files;
    directory_t **dirs;
};

struct tree_t
{
    directory_t *root;
    int depth;
};
typedef struct tree_t tree_t;

struct player_t
{
    // Input control
    char data[INPUT_MAX];
    int cursor;

    int score;
};
typedef struct player_t player_t;

struct game_t
{
    GAMESTATE state;
    int difficulty,
        running;
    
    tree_t *current;
};
typedef struct game_t game_t;

struct menu_t
{
    int difficulty_cursor;
};
typedef struct menu_t menu_t;


void end_program();

#endif // !STRUCTURES_H