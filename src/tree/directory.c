#include "../headers/tree/directory.h"

directory_t *generate_directory(int desired_depth, int depth)
{
    directory_t *res = malloc(sizeof(directory_t));

    res->depth = depth;

    int nb_items = rand() % (3 + 1 - 0) + 0;

    int model[nb_items];
    int nb_dir = 0;
    
    int dir;
    for (int i = 0; i < nb_items+1; i++)
    {
        dir = rand() % (1 + 1 - 0) + 0;

        if (dir)
        {
            nb_dir++;
        }

        model[i] = dir;
    }

    int nb_files = nb_items - nb_dir;

    // TODO : What if only files are generated?
    res->dirs = malloc(sizeof(directory_t) * nb_dir);
    res->files = malloc(sizeof(file_t) * nb_files);

    
    
}