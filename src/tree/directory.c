#include "../headers/tree/directory.h"
#include "../headers/tree/file.h"
#include "../headers/words_database/name_generator.h"

directory_t *generate_directory(int desired_depth, int depth)
{
    directory_t *res = malloc(sizeof(directory_t));

    res->depth = depth;

    int nb_items = rand() % (4 + 1 - 0) + 0;

    generate_name(res->name);    

    if (desired_depth == depth)
    {
        res->dirs = NULL;
        res->files = malloc(sizeof(file_t) * nb_items);

        for (int i = 0; i < nb_items+1; i++)
        {
            res->files[i] = generate_file();
        }

        return res;
    }

    int model[nb_items];
    int nb_dir = 0;
    
    int dir;
    for (int i = 0; i < nb_items; i++)
    {
        dir = rand() % (1 + 1 - 0) + 0;

        if (dir)
        {
            nb_dir++;
        }

        model[i] = dir;
    }

    int nb_files = nb_items - nb_dir;

    if (!nb_dir) 
    {
        nb_dir++;
        // nb_files--;
    }

    assert(nb_dir != 0);
    // assert(nb_files != 0);

    res->dirs = malloc(sizeof(directory_t) * nb_dir);
    res->files = malloc(sizeof(file_t) * nb_files);

    res->nb_files = nb_files;
    res->nb_dirs = nb_dir;

    fprintf(stderr, "dir : %s. files : %d, dirs : %d\n", res->name, nb_files, nb_dir);

    for (int i = 0; i < nb_files; i++)
    {
        res->files[i] = generate_file();
    }
    
    for (int i = 0; i < nb_dir; i++)
    {
        res->dirs[i] = generate_directory(desired_depth, depth+1);
    }

    return res;
}

void render_directory(directory_t *dir, int line)
{
    mvprintw(line, (dir->depth * 2) + 1, dir->name);
    int acc = 0;
    if (dir->nb_files > 0)
    {
        for (int i = 0; i < dir->nb_files; ++i)
        {
            acc++;
            mvprintw(line+acc, (dir->depth+1 * 2) + 1, dir->files[i]->name);
        }
    }
    if (dir->nb_dirs > 0)
    {
        for (int i = 0; i < dir->nb_dirs; ++i)
        {
            acc++;
            render_directory(dir->dirs[i], line+acc);
        }
    }
}