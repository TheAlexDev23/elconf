#include <stdlib.h>
#include <stdio.h>
#include <cwalk.h>

#include <pel.h>
#include <pttui/easy.h>

char* filename;
char* db_loc;
#define PATH_MAX 200

int parse_input(int argc, char* argv[])
{
    if (!(argc == 2 || argc == 3))
    {
        return -1;
    }

    db_loc = malloc(PATH_MAX);
    cwk_path_join(argv[1], "/lib/pttui/lib/libperiodic-c/Periodic-Table-JSON/PeriodicTableJSON.json", db_loc, PATH_MAX);

    // Use default filename
    if (argc == 2)
    {
        filename = "output.png";
    }
    else if (argc == 4)
    {
        filename = argv[2];
    }

    return 0;
}

int render_element(periodic_element_t* element)
{

}

int main(int argc, char* argv[])
{
    if (parse_input(argc, argv))
    {
        fprintf(stderr, "Incorrect usage, provide the project root directory and either the filename or nothing\n");
        return -1;
    }

    pel_init(filename, 300, 300);
    periodic_element_t* element = pttui_easy_get_element(db_loc);

    render_element(element);

    periodic_free_element(element);
    free(db_loc);
    return 0;
}