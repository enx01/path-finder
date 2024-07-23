#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "../structures.h"

directory_t *generate_directory(int, int);
directory_t *gen_dir_aux(int, int, int, int);

void find_target(directory_t *);

void free_directory(directory_t *);

void render_directory(directory_t *);
void render_aux(directory_t *, int, int);

int directory_depth(directory_t *);
int nb_elements_in_dir(directory_t *);
int nb_aux(directory_t *dir, int res);

#endif //!DIRECTORY_H