#include "../headers/tree/file.h"
#include "../headers/words_database/name_generator.h"


file_t *generate_file()
{
    file_t *res = malloc(sizeof(file_t));

    generate_name(res->name);

    return res;    
}