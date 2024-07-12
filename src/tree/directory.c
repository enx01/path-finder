#include "../headers/tree/directory.h"
#include "../headers/tree/file.h"
#include "../headers/words_database/name_generator.h"

directory_t *generate_directory(int desired_depth, int desired_elements)
{
    return gen_dir_aux(desired_depth, desired_elements , 0, desired_elements);
}

directory_t *gen_dir_aux(int desired_depth, int desired_elements, int depth,
                        int remaining_elements)
{
    directory_t *dir = (directory_t *)malloc(sizeof(directory_t));
    
    generate_name(dir->name);
    
    dir->depth = depth;

    fprintf(stderr, "generating dir %s of depth %d\n",dir->name, dir->depth);
    

    // Randomly decide the number of files (0 to desired_elements/desired_depth)
    if (remaining_elements != 0)
    {
        do
        {
            dir->nb_files = rand() % (desired_elements/desired_depth);
        }
        while(dir->nb_files - remaining_elements >= 0);
    }
    

    if (dir->nb_files)
    {
        dir->files = (file_t **)malloc(dir->nb_files * sizeof(file_t *));
    
        // Generate files
        for (int i = 0; i < dir->nb_files; i++)
        {
            dir->files[i] = generate_file();
        }
    }

    if (depth == desired_depth)
    {
        dir->nb_dirs = 0;
        dir->dirs = NULL;
    }
    else 
    {
        // Randomly decide the number of subdirectories (1 to 3)
        dir->nb_dirs = rand() % (2 + 1 - 1) + 1;

        dir->dirs = malloc(dir->nb_dirs * sizeof(directory_t *));
    
        // Recursively generate subdirectories
        for (int i = 0; i < dir->nb_dirs; i++)
        {
            dir->dirs[i] = gen_dir_aux(desired_depth,
                                        desired_elements,
                                        depth + 1,
                                        remaining_elements - (dir->nb_files));
        }

    }
    
    return dir;
}

void free_directory(directory_t *dir)
{
    for (int i = 0; i < dir->nb_files; ++i)
    {
        fprintf(stderr, "freeing file %s of dir %s\n", dir->files[i]->name,
                                                    dir->name);
        free(dir->files[i]);
    }
    
    if (dir->nb_files)
    {
        fprintf(stderr, "freeing file array of dir %s\n", dir->name);
        free(dir->files);
    }
    
    for (int i = 0; i < dir->nb_dirs; ++i)
    {
        fprintf(stderr, "freeing dir %s of dir %s\n", dir->dirs[i]->name,
                                                    dir->name);
        free_directory(dir->dirs[i]);
    }

    fprintf(stderr, "freeing dirs array of dir %s\n", dir->name);
    free(dir->dirs);


    fprintf(stderr, "freeing dir %s\n", dir->name);
    free(dir);
}

int nb_elements_in_dir(directory_t *dir)
{
    return nb_aux(dir, 1);
}

int nb_aux(directory_t *dir, int res)
{
    res += dir->nb_dirs + dir->nb_files;

    for (int i = 0; i < dir->nb_dirs; i++)
    {
        res += nb_aux(dir->dirs[i], 0);
    }

    return res;
}
    
void render_directory(directory_t *dir)
{
    mvprintw(1, 1, "-)");
    render_aux(dir, 1, 4);
}

void render_aux(directory_t *dir, int x, int y)
{
    mvprintw(x, y-1, "%s", dir->name);

    if (dir->nb_dirs + dir->nb_files >= 1)
    {
        int n = (nb_elements_in_dir(dir)*2);

        for (int i = x+1; i < n-1; ++i)
        {
            mvprintw(i, y, "|");
        }
    }
    

    int newX = x+2;

    for (int i = 0; i < dir->nb_dirs; ++i)
    {
        mvaddch(newX, y, 'L');

        render_aux(dir->dirs[i], newX, y+4);

        newX += (nb_elements_in_dir(dir->dirs[i])*2);
    }

    for (int i = 0; i < dir->nb_files; ++i)
    {
        mvaddch(newX, y, 'L');

        mvprintw(newX, y + 3, "%s", dir->files[i]);

        newX += 2;
    }
}