#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "../structures.h"

directory_t *generate_directory(int);
directory_t *gen_dir_aux(int, int);
void render_directory(directory_t *, int, int, int *);

#endif //!DIRECTORY_H