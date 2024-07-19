#ifndef STRUCTURES_H
#define STRUCTURES_H
#define INPUT_MAX 255
#define GAME_WIDTH 50
#define GAME_HEIGHT 30
#define MAX_WORDS 100
#define FRAME_RATE 20
#define FRAME_DELAY_NS 1000000000 / FRAME_RATE // in nanoseconds

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <locale.h>
#include <time.h>

typedef enum GAMESTATE {MENU, IN_GAME} GAMESTATE;
typedef enum ACTION {
    UP_MENU_CTRL, DOWN_MENU_CTRL,
    LEFT_MENU_CTRL, RIGHT_MENU_CTRL,
    OK_MENU, COMPUTE, QUIT
} ACTION;

struct name_generator
{
    char *db[MAX_WORDS];
    int used[MAX_WORDS];
};
typedef struct name_generator name_generator;

extern name_generator *ng;
extern struct timespec ts;

struct file_t
{
    char name[10];
    int target;
};
typedef struct file_t file_t;

typedef struct directory_t directory_t;
struct directory_t
{
    char name[10];
    
    file_t **files;
    int nb_files;

    directory_t **dirs;
    int nb_dirs;

    int depth;
};


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
    
    directory_t *current;
};
typedef struct game_t game_t;

struct menu_t
{
    int difficulty_cursor;
};
typedef struct menu_t menu_t;


void end_program();

#endif // !STRUCTURES_H