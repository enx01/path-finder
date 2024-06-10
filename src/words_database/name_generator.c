#include "../headers/words_database/name_generator.h"

name_generator *create_ng(const char *filename)
{
    name_generator *res = malloc(sizeof(name_generator));

    for (int i = 0; i < MAX_WORDS; ++i)
    {
        res->used[i] = 0;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read the entire file content
    char buffer[4096]; // Adjust size as necessary
    if (fgets(buffer, sizeof(buffer), file) == NULL)
    {
        perror("Error reading file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);

    // Tokenize the content using ';' as delimiter
    char *token = strtok(buffer, ";");
    int num = 0;

    while (token != NULL && num < MAX_WORDS) 
    {
        res->db[num] = malloc(strlen(token) + 1);
        if (res->db[num] == NULL)
        {
            perror("Error allocating memory");
            exit(EXIT_FAILURE);
        }
        strcpy(res->db[num], token);
        num++;
        token = strtok(NULL, ";");
    }

    return res;
}

void generate_name(char *name)
{
    for (int i = 0; i < MAX_WORDS; i++)
    {
        if (!ng->used[i]) 
        {
            strcpy(name, ng->db[i]);

            ng->used[i] = 1;

            return;
        }
    }
    
}