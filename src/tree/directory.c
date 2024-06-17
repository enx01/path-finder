#include "../headers/tree/directory.h"
#include "../headers/tree/file.h"
#include "../headers/words_database/name_generator.h"

// directory_t *generate_directory(int desired_depth, int depth)
// {
//     directory_t *res = malloc(sizeof(directory_t));

//     res->depth = depth;

//     int nb_items = rand() % (2 + 1 - 0) + 0;

//     generate_name(res->name);    

//     if (desired_depth == depth)
//     {
//         res->dirs = NULL;
//         res->files = malloc(sizeof(file_t) * nb_items);

//         for (int i = 0; i < nb_items+1; i++)
//         {
//             res->files[i] = generate_file();
//         }

//         return res;
//     }

//     int model[nb_items];
//     int nb_dir = 0;
    
//     int dir;
//     for (int i = 0; i < nb_items; i++)
//     {
//         dir = rand() % (1 + 1 - 0) + 0;

//         if (dir)
//         {
//             nb_dir++;
//         }

//         model[i] = dir;
//     }

//     int nb_files = nb_items - nb_dir;

//     if (!nb_dir) 
//     {
//         nb_dir++;
//         // nb_files--;
//     }

//     assert(nb_dir != 0);
//     // assert(nb_files != 0);

//     res->dirs = malloc(sizeof(directory_t) * nb_dir);
//     res->files = malloc(sizeof(file_t) * nb_files);

//     res->nb_files = nb_files;
//     res->nb_dirs = nb_dir;

//     fprintf(stderr, "dir : %s. files : %d, dirs : %d\n", res->name, nb_files, nb_dir);

//     for (int i = 0; i < nb_files; i++)
//     {
//         res->files[i] = generate_file();
//     }
    
//     for (int i = 0; i < nb_dir; i++)
//     {
//         res->dirs[i] = generate_directory(desired_depth, depth+1);
//     }

//     return res;
// }

directory_t *generate_directory(int desired_depth)
{
    return gen_dir_aux(desired_depth, 0);
}

directory_t *gen_dir_aux(int desired_depth, int depth)
{
    directory_t *dir = (directory_t *)malloc(sizeof(directory_t));
    
    
    generate_name(dir->name);
    
    dir->depth = depth;

    fprintf(stderr, "generating dir %s of depth %d\n",dir->name, dir->depth);
    
    if (depth == desired_depth)
    {
        dir->nb_dirs = 0;
        dir->dirs = NULL;
    }
    else 
    {
        // Randomly decide the number of subdirectories (1 to 3)
        dir->nb_dirs = rand() % (2 + 1 - 1) + 1;

        dir->dirs = (directory_t **)malloc(dir->nb_dirs * sizeof(directory_t *));
    
        // Recursively generate subdirectories
        for (int i = 0; i < dir->nb_dirs; i++)
        {
            dir->dirs[i] = gen_dir_aux(desired_depth, depth + 1);
        }

    }
    
    // Randomly decide the number of files (0 to 3)
    dir->nb_files = rand() % 4;
    if (dir->nb_files)
    {
        dir->files = (file_t **)malloc(dir->nb_files * sizeof(file_t *));
    
        // Generate files
        for (int i = 0; i < dir->nb_files; i++)
        {
            dir->files[i] = generate_file();
        }
    }

    
    
    return dir;
}

// int render_directory(directory_t *dir, int line, int is_last)
// {
//     // fprintf(stderr, "printing at depth = %d\n", dir->depth);
//     attron(COLOR_PAIR(2)); // Enable custom color 1
//     mvprintw(line, (dir->depth * 5) + 1, dir->name);
//     attroff(COLOR_PAIR(2)); // Disable custom color 1

//     int acc = 0;
//     if (dir->nb_dirs > 0)
//     {
//         for (int i = 0; i < dir->nb_dirs; ++i)
//         {
//             acc++;
//             acc += render_directory(dir->dirs[i], line+acc);
//         }
//     }
//     if (dir->nb_files > 0)
//     {
//         for (int i = 0; i < dir->nb_files; ++i)
//         {
//             acc++;
//             mvprintw(line+acc, (dir->depth+1 * 5) + 1, dir->files[i]->name);
//         }
//     }
//     // if (dir->nb_dirs > 0)
//     // {
//         // for (int i = 0; i < dir->nb_dirs; ++i)
//         // {
//         //     acc++;
//         //     render_directory(dir->dirs[i], line+acc);
//         // }
//     // }
//     return acc;
// }

void render_directory(directory_t *dir, int level, int is_last, int *row) {
    // Print the current directory name
    for (int i = 1; i < level; i++) {
        mvprintw(*row, i * 4, is_last ? "   " : " |  ");
    }
    if (level > 0) {
        mvprintw(*row, level * 4 - 4, is_last ? " o--" : " |--");
    }
    mvprintw(*row, level * 4, "%s", dir->name);
    (*row)++;

    // Print the files in the current directory
    for (int i = 0; i < dir->nb_files; i++) {
        for (int j = 0; j < level; j++) {
            mvprintw(*row, j * 4, " |  ");
        }
        mvprintw(*row, level * 4, " |--%s", dir->files[i]->name);
        (*row)++;
    }

    // Print the subdirectories recursively
    for (int i = 0; i < dir->nb_dirs; i++) {
        render_directory(dir->dirs[i], level + 1, i == dir->nb_dirs - 1, row);
    }
}

// void render_directory(directory_t *dir, int level, int is_last) {
//     // Print the current directory name
//     for (int i = 0; i < level; i++) {
//         fprintf(stderr, is_last ? "    " : " │   ");
//     }
//     if (level > 0) {
//         fprintf(stderr, is_last ? " └────" : " ├────");
//     }
//     fprintf(stderr, "%s\n", dir->name);

//     // Print the files in the current directory
//     for (int i = 0; i < dir->nb_files; i++) {
//         for (int j = 0; j <= level; j++) {
//             fprintf(stderr, " │   ");
//         }
//         fprintf(stderr, " ├────%s\n", dir->files[i]->name);
//     }

//     // Print the subdirectories recursively
//     for (int i = 0; i < dir->nb_dirs; i++) {
//         render_directory(dir->dirs[i], level + 1, i == dir->nb_dirs);
//     }
// }