#include "headers/game/game.h"
#include "headers/game/player.h"
#include "headers/words_database/name_generator.h"
#include "headers/menu/menu.h"

player_t *player;

menu_t *menu;

game_t *game = NULL;

name_generator *ng;

struct timespec ts;

void setup_ncurses() 
{
    // NOTE: All ncurses operations (getch, mvaddch, refresh, etc.) must be done on the same thread.
    initscr();
    raw();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
}

void restore_ncurses() 
{
    curs_set(1);
    endwin();
}

void end_program()
{
    free(player);
    free(menu);
    
    if (game != NULL) free_game(game);

    restore_ncurses();
    exit(EXIT_SUCCESS);
}

int main()
{
    setup_ncurses();
    srand(time(NULL)); 

    ng = create_ng("res/words.txt");

    ts.tv_sec = 0;
    ts.tv_nsec = FRAME_DELAY_NS;

    player = init_player();

    menu = init_menu();

    game = run_menu(menu, player);

    assert(game != NULL);

    run_game(game, player);

    restore_ncurses();
    return EXIT_SUCCESS;
}
