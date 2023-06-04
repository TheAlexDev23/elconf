#include <stdlib.h>
#include <stdio.h>
#include <cwalk.h>
#include <math.h>

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

double to_radians(double deg)
{
    return deg * M_PI / 180.0;
}

#define SHELL_SPACE 8
int render_element(periodic_element_t* element)
{
    for (int i = 0; i < element->conf.shells_amnt; i++)
    {
        // Draw shell
        pel_draw_circle(filename, PEL_COLOR_BLACK, 0, 0, SHELL_SPACE * (i + 1));

        int electrons = element->conf.shells[i];

        float angleDiff = 360.0 / (float)electrons;
        float angleDiffr = to_radians(angleDiff);
        for (int j = 0; j < electrons; j++)
        {
            int x = sin(j * angleDiffr) * SHELL_SPACE * (i + 1);
            int y = cos(j * angleDiffr) * SHELL_SPACE * (i + 1);

            pel_draw_circle_full(filename, PEL_COLOR_RED, x, y, 2);
        }
    }
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