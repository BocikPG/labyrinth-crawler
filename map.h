#ifndef _map_h_
#define _map_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAP_SIZE 34 + 2 //powinien być parzysty +2 dla ściań bocznych

enum exit_or_block_position{
    top_left,
    bottom_left,
    top_right,
    bottom_right,
    everywhere, 
    nowhere//is unused
};

struct map_template_chunk{
    char template_chunk[2][2];
    int is_mostly_path; // 0 = block , 1 = path, 2 = equal
    enum exit_or_block_position position; //if is_mostly_path == 0 || 2 positoin of path else position of block
    enum exit_or_block_position position2; //if unused == nowhere
    int number_of_paths;
    int in_place; // if exist in minimap == 1
};

char** map_generate();
char** set_treasure(char **map);


#endif