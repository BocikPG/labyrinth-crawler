#include "map.h"

char **map_generate()
{
    char **new_map = (char**)calloc(MAP_SIZE, sizeof(char *));
    if (new_map == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < MAP_SIZE; i++)
    {
        *(new_map + i) = (char*)calloc(MAP_SIZE + 3, sizeof(char));
        if (*(new_map + i) == NULL)
        {
            return NULL;
        }
    } //koniec alokacji pamięci na mapę

    //tworzenie ramki

    for (int j = 0; j < MAP_SIZE; j++) //górna i dolna granica
    {
        *(*(new_map) + j) = '|';
        *(*(new_map + MAP_SIZE - 1) + j) = '|';
    }
    *(*(new_map) + MAP_SIZE) = '\n';
    *(*(new_map + MAP_SIZE - 1) + MAP_SIZE) = '\n';

    for (int i = 1; i < MAP_SIZE - 1; i++)
    {
        *(*(new_map + i)) = '|';
        for (int j = 1; j < MAP_SIZE; j++)
        {
            *(*(new_map + i) + j) = ' ';
        }
        *(*(new_map + i) + MAP_SIZE - 1) = '|';
        *(*(new_map + i) + MAP_SIZE) = '\n';
    }

    //koniec tworzenia ramki i wypełniania pustymi polami obszaru gry
    //tworzenie klocków z których będę budował mapę (16-ście wzorców)

    struct map_template_chunk mt_no_exit;  // ||
    mt_no_exit.template_chunk[0][0] = '|'; // ||
    mt_no_exit.template_chunk[0][1] = '|';
    mt_no_exit.template_chunk[1][0] = '|';
    mt_no_exit.template_chunk[1][1] = '|';
    mt_no_exit.is_mostly_path = 0;
    mt_no_exit.position = everywhere;
    mt_no_exit.position2 = nowhere;
    mt_no_exit.number_of_paths = 0;
    mt_no_exit.in_place = 0;

    // struct map_template_chunk mt_all_exit;  //
    // mt_all_exit.template_chunk[0][0] = ' '; //
    // mt_all_exit.template_chunk[0][1] = ' ';
    // mt_all_exit.template_chunk[1][0] = ' ';
    // mt_all_exit.template_chunk[1][1] = ' ';
    // mt_all_exit.is_mostly_path = 1;
    // mt_all_exit.position = everywhere;
    // mt_all_exit.position2 = nowhere;
    // mt_all_exit.number_of_paths = 2;
    // mt_all_exit.in_place = 0;

    //pojedyńcze ścieżki

    struct map_template_chunk mt_top_left_exit;  //  |
    mt_top_left_exit.template_chunk[0][0] = ' '; // ||
    mt_top_left_exit.template_chunk[0][1] = '|';
    mt_top_left_exit.template_chunk[1][0] = '|';
    mt_top_left_exit.template_chunk[1][1] = '|';
    mt_top_left_exit.is_mostly_path = 0;
    mt_top_left_exit.position = top_left;
    mt_top_left_exit.position2 = nowhere;
    mt_top_left_exit.number_of_paths = 1;
    mt_top_left_exit.in_place = 0;

    struct map_template_chunk mt_top_right_exit;  // |
    mt_top_right_exit.template_chunk[0][0] = '|'; // ||
    mt_top_right_exit.template_chunk[0][1] = ' ';
    mt_top_right_exit.template_chunk[1][0] = '|';
    mt_top_right_exit.template_chunk[1][1] = '|';
    mt_top_right_exit.is_mostly_path = 0;
    mt_top_right_exit.position = top_right;
    mt_top_right_exit.position2 = nowhere;
    mt_top_right_exit.number_of_paths = 1;
    mt_top_right_exit.in_place = 0;

    struct map_template_chunk mt_bottom_left_exit;  // ||
    mt_bottom_left_exit.template_chunk[0][0] = '|'; //  |
    mt_bottom_left_exit.template_chunk[0][1] = '|';
    mt_bottom_left_exit.template_chunk[1][0] = ' ';
    mt_bottom_left_exit.template_chunk[1][1] = '|';
    mt_bottom_left_exit.is_mostly_path = 0;
    mt_bottom_left_exit.position = bottom_left;
    mt_bottom_left_exit.position2 = nowhere;
    mt_bottom_left_exit.number_of_paths = 1;
    mt_bottom_left_exit.in_place = 0;

    struct map_template_chunk mt_bottom_right_exit;  // ||
    mt_bottom_right_exit.template_chunk[0][0] = '|'; // |
    mt_bottom_right_exit.template_chunk[0][1] = '|';
    mt_bottom_right_exit.template_chunk[1][0] = '|';
    mt_bottom_right_exit.template_chunk[1][1] = ' ';
    mt_bottom_right_exit.is_mostly_path = 0;
    mt_bottom_right_exit.position = bottom_right;
    mt_bottom_right_exit.position2 = nowhere;
    mt_bottom_right_exit.number_of_paths = 1;
    mt_bottom_right_exit.in_place = 0;

    //pojedyńcze blokady

    struct map_template_chunk mt_except_bottom_right_exit;  //
    mt_except_bottom_right_exit.template_chunk[0][0] = ' '; //  |
    mt_except_bottom_right_exit.template_chunk[0][1] = ' ';
    mt_except_bottom_right_exit.template_chunk[1][0] = ' ';
    mt_except_bottom_right_exit.template_chunk[1][1] = '|';
    mt_except_bottom_right_exit.is_mostly_path = 1;
    mt_except_bottom_right_exit.position = bottom_right;
    mt_except_bottom_right_exit.position2 = nowhere;
    mt_except_bottom_right_exit.number_of_paths = 2;
    mt_except_bottom_right_exit.in_place = 0;

    struct map_template_chunk mt_except_bottom_left_exit;  //
    mt_except_bottom_left_exit.template_chunk[0][0] = ' '; // |
    mt_except_bottom_left_exit.template_chunk[0][1] = ' ';
    mt_except_bottom_left_exit.template_chunk[1][0] = '|';
    mt_except_bottom_left_exit.template_chunk[1][1] = ' ';
    mt_except_bottom_left_exit.is_mostly_path = 1;
    mt_except_bottom_left_exit.position = bottom_left;
    mt_except_bottom_left_exit.position2 = nowhere;
    mt_except_bottom_left_exit.number_of_paths = 2;
    mt_except_bottom_left_exit.in_place = 0;

    struct map_template_chunk mt_except_top_right_exit;  //  |
    mt_except_top_right_exit.template_chunk[0][0] = ' '; //
    mt_except_top_right_exit.template_chunk[0][1] = '|';
    mt_except_top_right_exit.template_chunk[1][0] = ' ';
    mt_except_top_right_exit.template_chunk[1][1] = ' ';
    mt_except_top_right_exit.is_mostly_path = 1;
    mt_except_top_right_exit.position = top_right;
    mt_except_top_right_exit.position2 = nowhere;
    mt_except_top_right_exit.number_of_paths = 2;
    mt_except_top_right_exit.in_place = 0;

    struct map_template_chunk mt_except_top_left_exit;  // |
    mt_except_top_left_exit.template_chunk[0][0] = '|'; //
    mt_except_top_left_exit.template_chunk[0][1] = ' ';
    mt_except_top_left_exit.template_chunk[1][0] = ' ';
    mt_except_top_left_exit.template_chunk[1][1] = ' ';
    mt_except_top_left_exit.is_mostly_path = 1;
    mt_except_top_left_exit.position = top_left;
    mt_except_top_left_exit.position2 = nowhere;
    mt_except_top_left_exit.number_of_paths = 2;
    mt_except_top_left_exit.in_place = 0;

    //po równo

    struct map_template_chunk mt_double_top_exit;  //
    mt_double_top_exit.template_chunk[0][0] = ' '; // ||
    mt_double_top_exit.template_chunk[0][1] = ' ';
    mt_double_top_exit.template_chunk[1][0] = '|';
    mt_double_top_exit.template_chunk[1][1] = '|';
    mt_double_top_exit.is_mostly_path = 2;
    mt_double_top_exit.position = top_left;
    mt_double_top_exit.position2 = top_right;
    mt_double_top_exit.number_of_paths = 1;
    mt_double_top_exit.in_place = 0;

    struct map_template_chunk mt_double_bottom_exit;  // ||
    mt_double_bottom_exit.template_chunk[0][0] = '|'; //
    mt_double_bottom_exit.template_chunk[0][1] = '|';
    mt_double_bottom_exit.template_chunk[1][0] = ' ';
    mt_double_bottom_exit.template_chunk[1][1] = ' ';
    mt_double_bottom_exit.is_mostly_path = 2;
    mt_double_bottom_exit.position = bottom_left;
    mt_double_bottom_exit.position2 = bottom_right;
    mt_double_bottom_exit.number_of_paths = 2;
    mt_double_bottom_exit.in_place = 0;

    struct map_template_chunk mt_double_left_exit;  // |
    mt_double_left_exit.template_chunk[0][0] = '|'; // |
    mt_double_left_exit.template_chunk[0][1] = ' ';
    mt_double_left_exit.template_chunk[1][0] = '|';
    mt_double_left_exit.template_chunk[1][1] = ' ';
    mt_double_left_exit.is_mostly_path = 2;
    mt_double_left_exit.position = top_right;
    mt_double_left_exit.position2 = bottom_right;
    mt_double_left_exit.number_of_paths = 2;
    mt_double_left_exit.in_place = 0;

    struct map_template_chunk mt_double_right_exit;  //  |
    mt_double_right_exit.template_chunk[0][0] = ' '; //  |
    mt_double_right_exit.template_chunk[0][1] = '|';
    mt_double_right_exit.template_chunk[1][0] = ' ';
    mt_double_right_exit.template_chunk[1][1] = '|';
    mt_double_right_exit.is_mostly_path = 2;
    mt_double_right_exit.position = top_left;
    mt_double_right_exit.position2 = bottom_left;
    mt_double_right_exit.number_of_paths = 1;
    mt_double_right_exit.in_place = 0;

    struct map_template_chunk mt_double_cross_top_right_exit;  // |
    mt_double_cross_top_right_exit.template_chunk[0][0] = '|'; //  |
    mt_double_cross_top_right_exit.template_chunk[0][1] = ' ';
    mt_double_cross_top_right_exit.template_chunk[1][0] = ' ';
    mt_double_cross_top_right_exit.template_chunk[1][1] = '|';
    mt_double_cross_top_right_exit.is_mostly_path = 2;
    mt_double_cross_top_right_exit.position = top_right;
    mt_double_cross_top_right_exit.position2 = bottom_left;
    mt_double_cross_top_right_exit.number_of_paths = 1;
    mt_double_cross_top_right_exit.in_place = 0;

    struct map_template_chunk mt_double_cross_top_left_exit;  //  |
    mt_double_cross_top_left_exit.template_chunk[0][0] = ' '; // |
    mt_double_cross_top_left_exit.template_chunk[0][1] = '|';
    mt_double_cross_top_left_exit.template_chunk[1][0] = '|';
    mt_double_cross_top_left_exit.template_chunk[1][1] = ' ';
    mt_double_cross_top_left_exit.is_mostly_path = 2;
    mt_double_cross_top_left_exit.position = top_left;
    mt_double_cross_top_left_exit.position2 = bottom_right;
    mt_double_cross_top_left_exit.number_of_paths = 1;
    mt_double_cross_top_left_exit.in_place = 0;

    //koniec tworzenia klocków
    //tworzenie mapy

    srand(time(NULL));

    //tworzenie mini mapy z klocków

    int mini_map_size = (MAP_SIZE - 2) / 2;
    struct map_template_chunk **mini_map = (struct map_template_chunk**)calloc(mini_map_size, sizeof(struct map_template_chunk *));
    if (mini_map == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < (MAP_SIZE - 2) / 2; i++)
    {
        *(mini_map + i) = (struct map_template_chunk*)calloc(mini_map_size + 1, sizeof(struct map_template_chunk));
        if (*(mini_map + i) == NULL)
        {
            return NULL;
        }
    } //koniec alokacji pamięci na mini mapę

    int seed = rand() % 12;
    switch (seed) //ustawiam pierwszy kwadrat z którego będę ciagnął trasy
    {
    //
    case 0:
        *(*(mini_map)) = mt_top_right_exit;
        (*(mini_map))->in_place = 1;
        break;
    case 1:
        *(*(mini_map)) = mt_bottom_left_exit;
        (*(mini_map))->in_place = 1;
        break;
    case 2:
        *(*(mini_map)) = mt_bottom_right_exit;
        (*(mini_map))->in_place = 1;
        break;
    case 3:
        *(*(mini_map)) = mt_except_bottom_right_exit;
        (*(mini_map))->in_place = 1;
        break;
    case 4:
        *(*(mini_map)) = mt_except_bottom_left_exit;
        (*(mini_map))->in_place = 1;
        break;
    case 5:
        *(*(mini_map)) = mt_except_top_right_exit;
        (*(mini_map))->in_place = 1;
        break;
    case 6:
        *(*(mini_map)) = mt_except_top_left_exit;
        (*(mini_map))->in_place = 1;
        break;
    case 7:
        *(*(mini_map)) = mt_double_top_exit;
        (*(mini_map))->in_place = 1;
        break;
    case 8:
        *(*(mini_map)) = mt_double_bottom_exit;
        (*(mini_map))->in_place = 1;
        break;
    case 9:
        *(*(mini_map)) = mt_double_left_exit;
        (*(mini_map))->in_place = 1;
        break;
    case 10:
        *(*(mini_map)) = mt_double_right_exit;
        (*(mini_map))->in_place = 1;
        break;
    case 11:
        *(*(mini_map)) = mt_double_cross_top_right_exit;
        (*(mini_map))->in_place = 1;
        break;
        //case 12:
        //     *(*(mini_map)) = mt_all_exit;
        //     (*(mini_map))->in_place = 1;
        //     break;
    }

    //układanie reszty klocków (większość jest przekopiowana - bardziej czasochłonne było myślenie koncepcyjne)
    //zalecam zwinąć :)

    for (int i = 0; i < mini_map_size; i++)
    {
        for (int j = 0; j < mini_map_size; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }

            if (i == 0) //gdy nie ma nic "nad" blokiem obecnym i j na pewno > 1 bo 1-wszy jest in_place
            {
                if ((((*(mini_map) + j - 1)->is_mostly_path == 0 || (*(mini_map) + j - 1)->is_mostly_path == 2) && (*(mini_map) + j - 1)->position == top_right) || (((*(mini_map) + j - 1)->is_mostly_path == 0 || (*(mini_map) + j - 1)->is_mostly_path == 2) && (*(mini_map) + j - 1)->position2 == top_right) || ((*(mini_map) + j - 1)->is_mostly_path == 1 && (*(mini_map) + j - 1)->position == everywhere) || ((*(mini_map + i) + j - 1)->is_mostly_path == 1 && (*(mini_map + i) + j - 1)->position != top_right)) //drugi warunek żeby nie zrobić korytarza bez dostępu do capsite'u
                {
                    if ((*(mini_map) + j - 1)->number_of_paths > 1)
                    {
                        seed = rand() % 6;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_no_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map) + j - 1)->number_of_paths -= 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map) + j - 1)->number_of_paths -= 1;

                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 5:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 6:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                    else
                    {
                        seed = rand() % 4;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                }
                else if ((((*(mini_map) + j - 1)->is_mostly_path == 0 || (*(mini_map) + j - 1)->is_mostly_path == 2) && (*(mini_map) + j - 1)->position == bottom_right) || (((*(mini_map) + j - 1)->is_mostly_path == 0 || (*(mini_map) + j - 1)->is_mostly_path == 2) && (*(mini_map) + j - 1)->position2 == bottom_right) || ((*(mini_map + i) + j - 1)->is_mostly_path == 1 && (*(mini_map + i) + j - 1)->position != bottom_right))
                {
                    if ((*(mini_map) + j - 1)->number_of_paths > 1)
                    {
                        seed = rand() % 7;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_no_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map) + j - 1)->number_of_paths -= 1;

                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 5:
                            *(*(mini_map + i) + j) = mt_double_bottom_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 6:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 1:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                    else
                    {
                        seed = rand() % 6;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_bottom_left_exit;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_double_bottom_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 5:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                }
                else
                {
                    int seed = rand() % 9;
                    switch (seed)
                    {
                    case 0:
                        *(*(mini_map + i) + j) = mt_bottom_left_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 1:
                        *(*(mini_map + i) + j) = mt_bottom_right_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 2:
                        *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 3:
                        *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 4:
                        *(*(mini_map + i) + j) = mt_except_top_right_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 5:
                        *(*(mini_map + i) + j) = mt_except_top_left_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 6:
                        *(*(mini_map + i) + j) = mt_double_bottom_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 7:
                        *(*(mini_map + i) + j) = mt_double_left_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 8:
                        *(*(mini_map + i) + j) = mt_double_right_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                        // case 0:
                        // *(*(mini_map + i) + j) = mt_all_exit;
                        // (*(mini_map + i) + j)->in_place = 1;
                        // break;
                    }
                }
                if (j >= mini_map_size - 1)
                {
                    (*(mini_map + i) + j)->number_of_paths = 1;
                }
                continue;
            }

            //gdy jest coś nad

            if (j == 0) //gdy nie ma poprzedniego
            {
                if ((((*(mini_map + i - 1))->is_mostly_path == 0 || (*(mini_map + i - 1))->is_mostly_path == 2) && (*(mini_map + i - 1))->position == bottom_left) || (((*(mini_map + i - 1))->is_mostly_path == 0 || (*(mini_map + i - 1))->is_mostly_path == 2) && (*(mini_map + i - 1))->position2 == bottom_left) || ((*(mini_map + i - 1))->is_mostly_path == 1 && (*(mini_map + i - 1))->position == everywhere) || ((*(mini_map + i - 1) + j)->is_mostly_path == 1 && (*(mini_map + i - 1) + j)->position != bottom_left))
                {
                    if ((*(mini_map + i - 1))->number_of_paths > 1)
                    {
                        seed = rand() % 8;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_no_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 5:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 6:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 7:
                            *(*(mini_map + i) + j) = mt_double_cross_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 1:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                    else
                    {
                        seed = rand() % 5;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                }
                else if ((((*(mini_map + i - 1))->is_mostly_path == 0 || (*(mini_map + i - 1))->is_mostly_path == 2) && (*(mini_map + i - 1))->position == bottom_right) || (((*(mini_map + i - 1))->is_mostly_path == 0 || (*(mini_map + i - 1))->is_mostly_path == 2) && (*(mini_map + i - 1))->position2 == bottom_right) || ((*(mini_map + i - 1) + j)->is_mostly_path == 1 && (*(mini_map + i - 1) + j)->position != bottom_right))
                {
                    if ((*(mini_map) + j - 1)->number_of_paths > 1)
                    {
                        seed = rand() % 7;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_no_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map) + j - 1)->number_of_paths -= 1;

                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 5:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 6:
                            *(*(mini_map + i) + j) = mt_double_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 1:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                    else
                    {
                        seed = rand() % 7;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 5:
                            *(*(mini_map + i) + j) = mt_double_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 6:
                            *(*(mini_map + i) + j) = mt_double_cross_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                }
                else
                {
                    int seed = rand() % 9;
                    switch (seed) //ustawiam pierwszy kwadrat z którego będę ciagnął trasy
                    {
                    case 0:
                        *(*(mini_map + i) + j) = mt_top_right_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 1:
                        *(*(mini_map + i) + j) = mt_bottom_right_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 2:
                        *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 3:
                        *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 4:
                        *(*(mini_map + i) + j) = mt_except_top_right_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 5:
                        *(*(mini_map + i) + j) = mt_except_top_left_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 6:
                        *(*(mini_map + i) + j) = mt_double_top_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 7:
                        *(*(mini_map + i) + j) = mt_double_bottom_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 8:
                        *(*(mini_map + i) + j) = mt_double_left_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                        // case 0:
                        // *(*(mini_map + i) + j) = mt_all_exit;
                        // (*(mini_map + i) + j)->in_place = 1;
                        // break;
                    }
                }
                if (i >= mini_map_size - 1)
                {
                    (*(mini_map + i) + j)->number_of_paths = 1;
                }
                continue;
            }

            //gdy jest coś nad i przed

            if ((((*(mini_map + i) + j - 1)->is_mostly_path == 0 || (*(mini_map + i) + j - 1)->is_mostly_path == 2) && (*(mini_map + i) + j - 1)->position == top_right) || (((*(mini_map + i) + j - 1)->is_mostly_path == 0 || (*(mini_map + i) + j - 1)->is_mostly_path == 2) && (*(mini_map + i) + j - 1)->position2 == top_right) || ((*(mini_map + i) + j - 1)->is_mostly_path == 1 && (*(mini_map + i) + j - 1)->position == everywhere) || ((*(mini_map + i) + j - 1)->is_mostly_path == 1 && (*(mini_map + i) + j - 1)->position != top_right))
            { // poprzedni w lewo ma ścierzkę w prawym-górnym rogu (lub wszędzie)
                if ((((*(mini_map + i - 1) + j)->is_mostly_path == 0 || (*(mini_map + i - 1) + j)->is_mostly_path == 2) && (*(mini_map + i - 1) + j)->position == bottom_left) || (((*(mini_map + i - 1) + j)->is_mostly_path == 0 || (*(mini_map + i - 1) + j)->is_mostly_path == 2) && (*(mini_map + i - 1) + j)->position2 == bottom_left) || ((*(mini_map + i - 1) + j)->is_mostly_path == 1 && (*(mini_map + i - 1) + j)->position == everywhere) || ((*(mini_map + i - 1) + j)->is_mostly_path == 1 && (*(mini_map + i - 1) + j)->position != bottom_left))
                { // gdy poprzedni nad ma ścierzkę w lewym dolnym
                    if ((*(mini_map + i - 1) + j)->number_of_paths > 1 && (*(mini_map + i) + j - 1)->number_of_paths > 1)
                    { //jeżeli zrobić ślepe uliczki
                        seed = rand() % 13;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_no_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 5:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 6:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 7:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 8:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 9:
                            *(*(mini_map + i) + j) = mt_double_bottom_exit; //??
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 10:
                            *(*(mini_map + i) + j) = mt_double_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 11:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 12:
                            *(*(mini_map + i) + j) = mt_double_cross_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                            // case 1:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                    else
                    {
                        seed = rand() % 3;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                }
                else if ((((*(mini_map + i - 1) + j)->is_mostly_path == 0 || (*(mini_map + i - 1) + j)->is_mostly_path == 2) && (*(mini_map + i - 1) + j)->position == bottom_right) || (((*(mini_map + i - 1) + j)->is_mostly_path == 0 || (*(mini_map + i - 1) + j)->is_mostly_path == 2) && (*(mini_map + i - 1) + j)->position2 == bottom_right) || ((*(mini_map + i - 1) + j)->is_mostly_path == 1 && (*(mini_map + i - 1) + j)->position != bottom_right))
                {
                    if ((*(mini_map + i - 1) + j)->number_of_paths > 1 && (*(mini_map + i) + j - 1)->number_of_paths > 1)
                    { //jeżeli można zrobić ślepe
                        seed = rand() % 13;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_no_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 5:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 6:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 7:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 8:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 9:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 10:
                            *(*(mini_map + i) + j) = mt_double_bottom_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 11:
                            *(*(mini_map + i) + j) = mt_double_left_exit;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 12:
                            *(*(mini_map + i) + j) = mt_double_cross_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                            // case 1:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                    else
                    {
                        seed = rand() % 3;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                }
                else
                {
                    if ((*(mini_map + i - 1) + j)->number_of_paths > 1 && (*(mini_map + i) + j - 1)->number_of_paths > 1)
                    { //jeżeli można zrobić ślepe
                        seed = rand() % 5;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                    else
                    {
                        seed = rand() % 4;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                }
            }
            else if ((((*(mini_map + i) + j - 1)->is_mostly_path == 0 || (*(mini_map + i) + j - 1)->is_mostly_path == 2) && (*(mini_map + i) + j - 1)->position == bottom_right) || (((*(mini_map + i) + j - 1)->is_mostly_path == 0 || (*(mini_map + i) + j - 1)->is_mostly_path == 2) && (*(mini_map + i) + j - 1)->position2 == bottom_right) || ((*(mini_map + i) + j - 1)->is_mostly_path == 1 && (*(mini_map + i) + j - 1)->position != bottom_right))
            {
                if ((((*(mini_map + i - 1) + j)->is_mostly_path == 0 || (*(mini_map + i - 1) + j)->is_mostly_path == 2) && (*(mini_map + i - 1) + j)->position == bottom_left) || (((*(mini_map + i - 1) + j)->is_mostly_path == 0 || (*(mini_map + i - 1) + j)->is_mostly_path == 2) && (*(mini_map + i - 1) + j)->position2 == bottom_left) || ((*(mini_map + i - 1) + j)->is_mostly_path == 1 && (*(mini_map + i - 1) + j)->position == everywhere) || ((*(mini_map + i - 1) + j)->is_mostly_path == 1 && (*(mini_map + i - 1) + j)->position != bottom_left))
                { // gdy poprzedni nad ma ścierzkę w lewym dolnym
                    if ((*(mini_map + i - 1) + j)->number_of_paths > 1 && (*(mini_map + i) + j - 1)->number_of_paths > 1)
                    { //jeżeli zrobić ślepe uliczki
                        seed = rand() % 12;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 5:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 6:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 7:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 8:
                            *(*(mini_map + i) + j) = mt_double_bottom_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 9:
                            *(*(mini_map + i) + j) = mt_double_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 10:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 11:
                            *(*(mini_map + i) + j) = mt_double_cross_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                            //                         case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                    else
                    {
                        seed = rand() % 2;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                }
                else if ((((*(mini_map + i - 1) + j)->is_mostly_path == 0 || (*(mini_map + i - 1) + j)->is_mostly_path == 2) && (*(mini_map + i - 1) + j)->position == bottom_right) || (((*(mini_map + i - 1) + j)->is_mostly_path == 0 || (*(mini_map + i - 1) + j)->is_mostly_path == 2) && (*(mini_map + i - 1) + j)->position2 == bottom_right) || ((*(mini_map + i - 1) + j)->is_mostly_path == 1 && (*(mini_map + i - 1) + j)->position != bottom_right))
                {
                    if ((*(mini_map + i - 1) + j)->number_of_paths > 1 && (*(mini_map + i) + j - 1)->number_of_paths > 1)
                    { //jeżeli można zrobić ślepe
                        seed = rand() % 12;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_no_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 5:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 6:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 7:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 8:
                            *(*(mini_map + i) + j) = mt_double_bottom_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 9:
                            *(*(mini_map + i) + j) = mt_double_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 10:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 11:
                            *(*(mini_map + i) + j) = mt_double_cross_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                            //                         case 1:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                    else
                    {
                        seed = rand() % 2;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                }
                else
                {
                    if ((*(mini_map + i - 1) + j)->number_of_paths > 1 && (*(mini_map + i) + j - 1)->number_of_paths > 1)
                    { //jeżeli można zrobić ślepe
                        seed = rand() % 7;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_double_bottom_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                        case 5:
                            *(*(mini_map + i) + j) = mt_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 6:
                            *(*(mini_map + i) + j) = mt_double_cross_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            //                     case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                    else
                    {
                        seed = rand() % 4;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_double_bottom_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;
                            break;
                            //                     case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                }
            }
            else //po lewo nie ma sąsiedzctwa
            {
                if ((((*(mini_map + i - 1) + j)->is_mostly_path == 0 || (*(mini_map + i - 1) + j)->is_mostly_path == 2) && (*(mini_map + i - 1) + j)->position == bottom_left) || (((*(mini_map + i - 1) + j)->is_mostly_path == 0 || (*(mini_map + i - 1) + j)->is_mostly_path == 2) && (*(mini_map + i - 1) + j)->position2 == bottom_left) || ((*(mini_map + i - 1) + j)->is_mostly_path == 1 && (*(mini_map + i - 1) + j)->position == everywhere) || ((*(mini_map + i - 1) + j)->is_mostly_path == 1 && (*(mini_map + i - 1) + j)->position != bottom_left))
                { // gdy poprzedni nad ma ścierzkę w lewym dolnym
                    if ((*(mini_map + i - 1) + j)->number_of_paths > 1 && (*(mini_map + i) + j - 1)->number_of_paths > 1)
                    { //jeżeli zrobić ślepe uliczki
                        seed = rand() % 12;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 5:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 6:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 7:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 8:
                            *(*(mini_map + i) + j) = mt_double_bottom_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 9:
                            *(*(mini_map + i) + j) = mt_double_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 10:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 11:
                            *(*(mini_map + i) + j) = mt_double_cross_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            //                         case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                    else
                    {
                        seed = rand() % 5;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                            // case 0:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                }
                else if ((((*(mini_map + i - 1) + j)->is_mostly_path == 0 || (*(mini_map + i - 1) + j)->is_mostly_path == 2) && (*(mini_map + i - 1) + j)->position == bottom_right) || (((*(mini_map + i - 1) + j)->is_mostly_path == 0 || (*(mini_map + i - 1) + j)->is_mostly_path == 2) && (*(mini_map + i - 1) + j)->position2 == bottom_right) || ((*(mini_map + i - 1) + j)->is_mostly_path == 1 && (*(mini_map + i - 1) + j)->position != bottom_right))
                {
                    if ((*(mini_map + i - 1) + j)->number_of_paths > 1 && (*(mini_map + i) + j - 1)->number_of_paths > 1)
                    { //jeżeli można zrobić ślepe
                        seed = rand() % 14;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_no_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 4:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 5:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 6:
                            *(*(mini_map + i) + j) = mt_except_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 7:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                        case 8:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 9:
                            *(*(mini_map + i) + j) = mt_double_top_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 10:
                            *(*(mini_map + i) + j) = mt_double_bottom_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 11:
                            *(*(mini_map + i) + j) = mt_double_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 12:
                            *(*(mini_map + i) + j) = mt_double_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 13:
                            *(*(mini_map + i) + j) = mt_double_cross_top_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;

                            (*(mini_map + i) + j - 1)->number_of_paths -= 1;

                            break;
                            // case 1:
                            // *(*(mini_map + i) + j) = mt_all_exit;
                            // (*(mini_map + i) + j)->in_place = 1;
                            // break;
                        }
                    }
                    else
                    {
                        seed = rand() % 4;
                        switch (seed)
                        {
                        case 0:
                            *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 1:
                            *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 2:
                            *(*(mini_map + i) + j) = mt_except_top_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        case 3:
                            *(*(mini_map + i) + j) = mt_double_left_exit;
                            (*(mini_map + i) + j)->in_place = 1;
                            break;
                        }
                        // case 0:
                        //     *(*(mini_map + i) + j) = mt_all_exit;
                        //     (*(mini_map + i) + j)->in_place = 1;
                        //     break;
                    }
                }
                else
                {
                    int seed = rand() % 10;
                    switch (seed)
                    {
                    case 0:
                        *(*(mini_map + i) + j) = mt_top_right_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 1:
                        *(*(mini_map + i) + j) = mt_bottom_right_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 2:
                        *(*(mini_map + i) + j) = mt_except_bottom_right_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 3:
                        *(*(mini_map + i) + j) = mt_except_bottom_left_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 4:
                        *(*(mini_map + i) + j) = mt_except_top_right_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 5:
                        *(*(mini_map + i) + j) = mt_except_top_left_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 6:
                        *(*(mini_map + i) + j) = mt_double_top_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 7:
                        *(*(mini_map + i) + j) = mt_double_bottom_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 8:
                        *(*(mini_map + i) + j) = mt_double_left_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                    case 9:
                        *(*(mini_map + i) + j) = mt_double_right_exit;
                        (*(mini_map + i) + j)->in_place = 1;
                        break;
                        // case 0:
                        // *(*(mini_map + i) + j) = mt_all_exit;
                        // (*(mini_map + i) + j)->in_place = 1;
                        // break;
                    }
                }
            }

            if (j >= mini_map_size - 1 || i >= mini_map_size - 1)
            {
                (*(mini_map + i) + j)->number_of_paths = 1;
            }
        }
    }

    //koniec układania minimapy :V
    //tworzenie mapy na podstawie mini mapy

    for (int i = 0; i < mini_map_size; i++)
    {
        int j = 0;
        for (j; j < mini_map_size; j++)
        {
            if ((*(mini_map + i) + j)->in_place == 0)
            {
                continue;
            }
            *(*(new_map + 2 * i + 1) + 2 * j + 1) = (*(mini_map + i) + j)->template_chunk[0][0];
            *(*(new_map + 2 * i + 1) + 2 * j + 2) = (*(mini_map + i) + j)->template_chunk[0][1];
            *(*(new_map + 2 * i + 2) + 2 * j + 1) = (*(mini_map + i) + j)->template_chunk[1][0];
            *(*(new_map + 2 * i + 2) + 2 * j + 2) = (*(mini_map + i) + j)->template_chunk[1][1];
        }
        *(*(new_map + 2 * i + 1) + 2 * j + 1) = '|';
        *(*(new_map + 2 * i + 2) + 2 * j + 1) = '|';
        *(*(new_map + 2 * i + 1) + 2 * j + 2) = '\n';
        *(*(new_map + 2 * i + 2) + 2 * j + 2) = '\n';
    }

    //koniec tworzenia mapy na podstawie mini_mapy

    return new_map;
}

char **set_treasure(char **map)
{
    int amount = 0; //licznik nagród i krzaków
    do
    {
        amount = rand() % MAP_SIZE * 4;
    } while (amount < MAP_SIZE * 2);

    int i = (MAP_SIZE) / 2, j = (MAP_SIZE) / 2;
    while (1)
    {
        if (*(*(map + i) + j) == ' ')
        {
            *(*(map + i) + j) = 'A';
            break;
        }
        int znak = rand() % 2;
        if (znak == 0)
        {
            i += rand() % 2;
            j -= rand() % 2;
        }
        else
        {
            i -= rand() % 2;
            j += rand() % 2;
        }
        if (i >= MAP_SIZE || i < 0)
        {
            i = MAP_SIZE / 2;
        }
        if (j >= MAP_SIZE || j < 0)
        {
            j = MAP_SIZE / 2;
        }
    }

    //ustawianie capsite'u zakończone

    int k = 0;
    while (k < amount)
    {
        i = rand() % MAP_SIZE;
        j = rand() % MAP_SIZE;

        if (*(*(map + i) + j) == ' ')
        {
            int seed = rand() % 100;
            if (seed < 40)
            {
                *(*(map + i) + j) = '#';
            }
            else if (seed < 60)
            {
                *(*(map + i) + j) = 'c';
            }
            else if (seed < 85)
            {
                *(*(map + i) + j) = 't';
            }
            else if (seed < 100)
            {
                *(*(map + i) + j) = 'T';
            }
            k++;
        }
    }

    return map;
}
