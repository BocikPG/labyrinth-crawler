#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "serwer.h"

void *Beast::makeARequestToMoveThread(void *beastIGuess)
{
    Beast *beastPointer;
    beastPointer = (Beast *)beastIGuess;

    int start_checking_x, end_checking_x, start_checking_y, end_checking_y;

    if (beastPointer->position.x < 2)
    {
        start_checking_x = 0;
        end_checking_x = beastPointer->position.x + 2;
    }
    else if (beastPointer->position.x > MAP_SIZE - 3)
    {
        start_checking_x = beastPointer->position.x - 2;
        end_checking_x = MAP_SIZE;
    }
    else
    {
        start_checking_x = beastPointer->position.x - 2;
        end_checking_x = beastPointer->position.x + 2;
    }

    if (beastPointer->position.y < 2)
    {
        start_checking_y = 0;
        end_checking_y = beastPointer->position.y + 2;
    }
    else if (beastPointer->position.y > MAP_SIZE - 3)
    {
        start_checking_y = beastPointer->position.y - 2;
        end_checking_y = MAP_SIZE;
    }
    else
    {
        start_checking_y = beastPointer->position.y - 2;
        end_checking_y = beastPointer->position.y + 2;
    }

    // if affected by player presence the movement will be random, if not will be changed in for(for)
    int dir_seed = rand() % 5;

    switch (dir_seed)
    {
    case 0:
        beastPointer->dir = UP;
        break;
    case 1:
        beastPointer->dir = DOWN;
        break;
    case 2:
        beastPointer->dir = LEFT;
        break;
    case 3:
        beastPointer->dir = RIGHT;
        break;
    default:
        beastPointer->dir = STAY;
        break;
    }

    bool found = false;

    for (int i = start_checking_y; i < end_checking_y; i++)
    {
        for (int j = start_checking_x; j < end_checking_x; j++)
        {
            if (beastPointer->pieceOfMap[i][j] == '1' || beastPointer->pieceOfMap[i][j] == '2' || beastPointer->pieceOfMap[i][j] == '3' || beastPointer->pieceOfMap[i][j] == '4') // player is in view distance
            {
                if (i < beastPointer->position.y)
                {
                    if (j < beastPointer->position.x) //left top corner
                    {
                        if (beastPointer->pieceOfMap[beastPointer->position.y - 1][beastPointer->position.x - 1] == '|')
                        {
                            // just go further randomly
                        }
                        else if (beastPointer->pieceOfMap[beastPointer->position.y - 1][beastPointer->position.x] == ' ')
                        {
                            beastPointer->dir = UP;
                        }
                        else
                        {
                            beastPointer->dir = LEFT;
                        }
                    }
                    else if (j == beastPointer->position.x) //player is above
                    {
                        if (beastPointer->pieceOfMap[beastPointer->position.y - 1][beastPointer->position.x] == ' ')
                        {
                            beastPointer->dir = UP;
                        }
                    }
                    else //j > position.x   top right corner
                    {
                        if (beastPointer->pieceOfMap[beastPointer->position.y - 1][beastPointer->position.x + 1] == '|')
                        {
                            // just go further randomly
                        }
                        else if (beastPointer->pieceOfMap[beastPointer->position.y][beastPointer->position.x + 1] == ' ')
                        {
                            beastPointer->dir = RIGHT;
                        }
                        else
                        {
                            beastPointer->dir = UP;
                        }
                    }
                }
                else if (i == beastPointer->position.y)
                {
                    if (j < beastPointer->position.x) //left
                    {
                        if (beastPointer->pieceOfMap[beastPointer->position.y][beastPointer->position.x - 1] != '|')
                        {
                            beastPointer->dir = LEFT;
                        }
                    }
                    else //j > position.x   right
                    {
                        if (beastPointer->pieceOfMap[beastPointer->position.y][beastPointer->position.x + 1] != '|')
                        {
                            beastPointer->dir = RIGHT;
                        }
                    }
                }
                else // i > position.y
                {
                    if (beastPointer->pieceOfMap[beastPointer->position.y + 1][beastPointer->position.x - 1] == '|')
                    {
                        // just go further randomly
                    }
                    else if (j < beastPointer->position.x) //left bottom corner
                    {
                        if (beastPointer->pieceOfMap[beastPointer->position.y + 1][beastPointer->position.x] == ' ')
                        {
                            beastPointer->dir = DOWN;
                        }
                        else
                        {
                            beastPointer->dir = LEFT;
                        }
                    }
                    else if (j == beastPointer->position.x) //player is below
                    {
                        if (beastPointer->position.y - i == 1)
                        {
                            beastPointer->dir = DOWN;
                        }
                        else
                        {
                            if (beastPointer->pieceOfMap[beastPointer->position.y - 1][beastPointer->position.x] == ' ')
                            {
                                beastPointer->dir = DOWN;
                            }
                        }
                    }
                    else //j > position.x   bottom right corner
                    {
                        if (beastPointer->pieceOfMap[beastPointer->position.y + 1][beastPointer->position.x + 1] == '|')
                        {
                            // just go further randomly
                        }
                        else if (beastPointer->pieceOfMap[beastPointer->position.y][beastPointer->position.x + 1] == ' ')
                        {
                            beastPointer->dir = RIGHT;
                        }
                        else
                        {
                            beastPointer->dir = DOWN;
                        }
                    }
                }
                found = true;
            }
            if (found)
            {
                break;
            }
        }
        if (found)
        {
            break;
        }
    }

    return beastPointer;
}

void Serwer::actualMoveBeast(Beast &toMove)
{
    if (toMove.inBush)
    {
        toMove.inBush = false;
        return;
    }

    switch (toMove.dir)
    {
    case 0: //UP
        if (*(*(map + toMove.position.y - 1) + toMove.position.x) == '#')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y - 1) + toMove.position.x);
            toMove.position.y--;
            toMove.inBush = true;
        }
        else if (*(*(map + toMove.position.y - 1) + toMove.position.x) == '|')
        {
            toMove.inBush = false;
            break;
        }
        else if (*(*(map + toMove.position.y - 1) + toMove.position.x) >= '1' && *(*(map + toMove.position.y - 1) + toMove.position.x) <= '4')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            colisionWithBeast(toMove, players[(int)(*(*(map + toMove.position.y - 1) + toMove.position.x) - '1')]); //chaning charUnder of beast too
        }
        else if (*(*(map + toMove.position.y - 1) + toMove.position.x) == '*')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = ' ';
            toMove.position.y--;
            toMove.inBush = false;
        }
        else
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y - 1) + toMove.position.x);
            toMove.position.y--;
            toMove.inBush = false;
        }
        break;
    case 1: //DOWN
        if (*(*(map + toMove.position.y + 1) + toMove.position.x) == '#')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y + 1) + toMove.position.x);
            toMove.position.y++;
            toMove.inBush = true;
        }
        else if (*(*(map + toMove.position.y + 1) + toMove.position.x) == '|')
        {
            toMove.inBush = false;
            break;
        }
        else if (*(*(map + toMove.position.y + 1) + toMove.position.x) >= '1' && *(*(map + toMove.position.y + 1) + toMove.position.x) <= '4')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            colisionWithBeast(toMove, players[(int)(*(*(map + toMove.position.y + 1) + toMove.position.x) - '1')]); //chaning charUnder of beast too
        }
        else if (*(*(map + toMove.position.y + 1) + toMove.position.x) == '*')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = ' ';
            toMove.position.y++;
            toMove.inBush = false;
        }
        else //all tresures, campsite, and blank
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y + 1) + toMove.position.x);
            toMove.position.y++;
            toMove.inBush = false;
        }
        break;
    case 2: //LEFT
        if (*(*(map + toMove.position.y) + toMove.position.x - 1) == '#')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y) + toMove.position.x - 1);
            toMove.position.x--;
            toMove.inBush = true;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x - 1) == '|')
        {
            toMove.inBush = false;
            break;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x - 1) >= '1' && *(*(map + toMove.position.y) + toMove.position.x - 1) <= '4')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            colisionWithBeast(toMove, players[(int)(*(*(map + toMove.position.y) + toMove.position.x - 1) - '1')]); //chaning charUnder of beast too
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x - 1) == '*')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = ' ';
            toMove.position.x--;
            toMove.inBush = false;
        }
        else //all tresures, campsite, and blank
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y) + toMove.position.x - 1);
            toMove.position.x--;
            toMove.inBush = false;
        }
        break;
    case 3: //RIGHT
        if (*(*(map + toMove.position.y) + toMove.position.x + 1) == '#')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y) + toMove.position.x + 1);
            toMove.position.x++;
            toMove.inBush = true;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x + 1) == '|')
        {
            toMove.inBush = false;
            break;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x + 1) >= '1' && *(*(map + toMove.position.y) + toMove.position.x + 1) <= '4')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            colisionWithBeast(toMove, players[(int)(*(*(map + toMove.position.y) + toMove.position.x + 1) - '1')]); //chaning charUnder of beast too
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x + 1) == '*')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = ' ';
            toMove.position.x++;
            toMove.inBush = false;
        }
        else //all tresures, campsite, and blank
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y) + toMove.position.x + 1);
            toMove.position.x++;
            toMove.inBush = false;
        }
        break;
    case 4: //STAY
        break;
    }
    drawBeastOnMap(toMove);
    return;
}

void Serwer::actualMovePlayer(Player &toMove, enum direction dir)
{
    if(toMove.visible==false)
    {
        return;
    }
    if (toMove.inBush)
    {
        toMove.inBush = false;
        return;
    }

    if (*(*(map + toMove.position.y) + toMove.position.x) == 'D')
    {
        for (int i = 0; i < ds.size(); i++)
        {
            if (ds[i].position.x == toMove.position.x && ds[i].position.y == toMove.position.y)
            {
                toMove.carried += ds[i].value;
                toMove.charUnder = ds[i].charUnder;
                ds.erase(ds.begin() + i);
                break;
            }
        }
    }

    switch (dir)
    {
    case 0: //UP
        if (*(*(map + toMove.position.y - 1) + toMove.position.x) == '#')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y - 1) + toMove.position.x);
            toMove.position.y--;
            toMove.inBush = true;
        }
        else if (*(*(map + toMove.position.y - 1) + toMove.position.x) == '|')
        {
            toMove.inBush = false;
            break;
        }
        else if (*(*(map + toMove.position.y - 1) + toMove.position.x) >= '1' && *(*(map + toMove.position.y - 1) + toMove.position.x) <= '4')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            colisionWithPlayer(toMove, players[(int)(*(*(map + toMove.position.y - 1) + toMove.position.x) - '1')]); //chaning charUnder of beast too
        }
        else if (*(*(map + toMove.position.y - 1) + toMove.position.x) == 'c')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.carried += 1;
            toMove.charUnder = ' ';
            toMove.position.y--;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y - 1) + toMove.position.x) == 't')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.carried += 10;
            toMove.charUnder = ' ';
            toMove.position.y--;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y - 1) + toMove.position.x) == 'T')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.carried += 50;
            toMove.charUnder = ' ';
            toMove.position.y--;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y - 1) + toMove.position.x) == 'A')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.budget += toMove.carried;
            toMove.carried = 0;
            toMove.charUnder = 'A';
            toMove.position.y--;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y - 1) + toMove.position.x) == 'D')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.position.y--;
            for (int i = 0; i < ds.size(); i++)
            {
                if (ds[i].position.x == toMove.position.x && ds[i].position.y == toMove.position.y)
                {
                    toMove.carried += ds[i].value;
                    toMove.charUnder = ds[i].charUnder;
                    ds.erase(ds.begin() + i);
                    break;
                }
            }
            if (toMove.charUnder == '#')
            {
                toMove.inBush = true;
            }
            else if (toMove.charUnder == 'c') //shouldn't happen but just in case
            {
                toMove.carried++;
                toMove.charUnder = ' ';
            }
            else if (toMove.charUnder == 't')
            {
                toMove.carried += 10;
                toMove.charUnder = ' ';
            }
            else if (toMove.charUnder == 'T')
            {
                toMove.carried += 50;
                toMove.charUnder = ' ';
            }
        }
        else
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y - 1) + toMove.position.x);
            toMove.position.y--;
            toMove.inBush = false;
        }
        break;
    case 1: //DOWN
        if (*(*(map + toMove.position.y + 1) + toMove.position.x) == '#')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y + 1) + toMove.position.x);
            toMove.position.y++;
            toMove.inBush = true;
        }
        else if (*(*(map + toMove.position.y + 1) + toMove.position.x) == '|')
        {
            toMove.inBush = false;
            break;
        }
        else if (*(*(map + toMove.position.y + 1) + toMove.position.x) >= '1' && *(*(map + toMove.position.y + 1) + toMove.position.x) <= '4')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            colisionWithPlayer(toMove, players[(int)(*(*(map + toMove.position.y + 1) + toMove.position.x) - '1')]); //chaning charUnder of beast too
        }
        else if (*(*(map + toMove.position.y + 1) + toMove.position.x) == 'c')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.carried += 1;
            toMove.charUnder = ' ';
            toMove.position.y++;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y + 1) + toMove.position.x) == 't')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.carried += 10;
            toMove.charUnder = ' ';
            toMove.position.y++;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y + 1) + toMove.position.x) == 'T')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.carried += 50;
            toMove.charUnder = ' ';
            toMove.position.y++;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y + 1) + toMove.position.x) == 'A')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.budget += toMove.carried;
            toMove.carried = 0;
            toMove.charUnder = 'A';
            toMove.position.y++;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y + 1) + toMove.position.x) == 'D')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.position.y++;
            for (int i = 0; i < ds.size(); i++)
            {
                if (ds[i].position.x == toMove.position.x && ds[i].position.y == toMove.position.y)
                {
                    toMove.carried += ds[i].value;
                    toMove.charUnder = ds[i].charUnder;
                    ds.erase(ds.begin() + i);
                    break;
                }
            }
            if (toMove.charUnder == '#')
            {
                toMove.inBush = true;
            }
            else if (toMove.charUnder == 'c') //shouldn't happen but just in case
            {
                toMove.carried++;
                toMove.charUnder = ' ';
            }
            else if (toMove.charUnder == 't')
            {
                toMove.carried += 10;
                toMove.charUnder = ' ';
            }
            else if (toMove.charUnder == 'T')
            {
                toMove.carried += 50;
                toMove.charUnder = ' ';
            }
        }
        else //all treasures, campsite, and blank
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y + 1) + toMove.position.x);
            toMove.position.y++;
            toMove.inBush = false;
        }
        break;
    case 2: //LEFT
        if (*(*(map + toMove.position.y) + toMove.position.x - 1) == '#')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y) + toMove.position.x - 1);
            toMove.position.x--;
            toMove.inBush = true;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x - 1) == '|')
        {
            toMove.inBush = false;
            break;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x - 1) >= '1' && *(*(map + toMove.position.y) + toMove.position.x - 1) <= '4')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            colisionWithPlayer(toMove, players[(int)(*(*(map + toMove.position.y) + toMove.position.x - 1) - '1')]); //chaning charUnder of beast too
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x - 1) == 'c')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.carried += 1;
            toMove.charUnder = ' ';
            toMove.position.x--;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x - 1) == 't')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.carried += 10;
            toMove.charUnder = ' ';
            toMove.position.x--;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x - 1) == 'T')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.carried += 50;
            toMove.charUnder = ' ';
            toMove.position.x--;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x - 1) == 'A')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.budget += toMove.carried;
            toMove.carried = 0;
            toMove.charUnder = 'A';
            toMove.position.x--;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x - 1) == 'D')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.position.x--;
            for (int i = 0; i < ds.size(); i++)
            {
                if (ds[i].position.x == toMove.position.x && ds[i].position.y == toMove.position.y)
                {
                    toMove.carried += ds[i].value;
                    toMove.charUnder = ds[i].charUnder;
                    ds.erase(ds.begin() + i);
                    break;
                }
            }
            if (toMove.charUnder == '#')
            {
                toMove.inBush = true;
            }
            else if (toMove.charUnder == 'c') //shouldn't happen but just in case
            {
                toMove.carried++;
                toMove.charUnder = ' ';
            }
            else if (toMove.charUnder == 't')
            {
                toMove.carried += 10;
                toMove.charUnder = ' ';
            }
            else if (toMove.charUnder == 'T')
            {
                toMove.carried += 50;
                toMove.charUnder = ' ';
            }
        }
        else //all treasures, campsite, and blank
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y) + toMove.position.x - 1);
            toMove.position.x--;
            toMove.inBush = false;
        }
        break;
    case 3: //RIGHT
        if (*(*(map + toMove.position.y) + toMove.position.x + 1) == '#')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y) + toMove.position.x + 1);
            toMove.position.x++;
            toMove.inBush = true;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x + 1) == '|')
        {
            toMove.inBush = false;
            break;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x + 1) >= '1' && *(*(map + toMove.position.y) + toMove.position.x + 1) <= '4')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            colisionWithPlayer(toMove, players[(int)(*(*(map + toMove.position.y) + toMove.position.x + 1) - '1')]); //chaning charUnder of beast too
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x + 1) == 'c')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.carried += 1;
            toMove.charUnder = ' ';
            toMove.position.x++;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x + 1) == 't')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.carried += 10;
            toMove.charUnder = ' ';
            toMove.position.x++;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x + 1) == 'T')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.carried += 50;
            toMove.charUnder = ' ';
            toMove.position.x++;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x + 1) == 'A')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.budget += toMove.carried;
            toMove.carried = 0;
            toMove.charUnder = 'A';
            toMove.position.x++;
            toMove.inBush = false;
        }
        else if (*(*(map + toMove.position.y) + toMove.position.x + 1) == 'D')
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.position.x++;
            for (int i = 0; i < ds.size(); i++)
            {
                if (ds[i].position.x == toMove.position.x && ds[i].position.y == toMove.position.y)
                {
                    toMove.carried += ds[i].value;
                    toMove.charUnder = ds[i].charUnder;
                    ds.erase(ds.begin() + i);
                    break;
                }
            }
            if (toMove.charUnder == '#')
            {
                toMove.inBush = true;
            }
            else if (toMove.charUnder == 'c') //shouldn't happen but just in case
            {
                toMove.carried++;
                toMove.charUnder = ' ';
            }
            else if (toMove.charUnder == 't')
            {
                toMove.carried += 10;
                toMove.charUnder = ' ';
            }
            else if (toMove.charUnder == 'T')
            {
                toMove.carried += 50;
                toMove.charUnder = ' ';
            }
        }
        else //all treasures, campsite, and blank
        {
            *(*(map + toMove.position.y) + toMove.position.x) = toMove.charUnder;
            toMove.charUnder = *(*(map + toMove.position.y) + toMove.position.x + 1);
            toMove.position.x++;
            toMove.inBush = false;
        }
        break;
    case 4: //STAY
        break;
    }

    *(*(map + toMove.position.y) + toMove.position.x) = toMove.number;

    return;
}

void Serwer::createPieceOfMap(Point position, char pieceOfMap[MAP_SIZE][MAP_SIZE + 3])
{

    for (int i = 0; i < MAP_SIZE + 2; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            if ((i >= position.x - 2 && i <= position.x + 2 && j >= position.y - 2 && j <= position.y + 2))
            {
                pieceOfMap[j][i] = *(*(map + j) + i);
            }
            else if (i >= MAP_SIZE)
            {
                pieceOfMap[j][i] = '\n';
            }
            else
            {
                pieceOfMap[j][i] = ' ';
            }
        }
    }

    return;
}

void Serwer::mapGenerate()
{
    map = map_generate();
    map = set_treasure(map);
}

void Serwer::mapDisplay()
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            mvprintw(i, j, "%c", *(*(map + i) + j));
        }
    }

    mvprintw(0, MAP_SIZE + 4, "PID Serwera: %5d", PID);
    mvprintw(1, MAP_SIZE + 4, "Numer tury: %5d", roundNumber);

    mvprintw(3, MAP_SIZE + 4, "Gracze:       Gracz1   Gracz2   Gracz3   Gracz4");
    mvprintw(4, MAP_SIZE + 4, "  PID:          %5d   %5d   %5d    %5d", players[0].PID, players[1].PID, players[2].PID, players[3].PID);
    mvprintw(5, MAP_SIZE + 4, "  Typ:          %s   %s   %s    %s", "HUMAN", "HUMAN", "HUMAN", "HUMAN"); //players[0].humanOrCPU
    mvprintw(6, MAP_SIZE + 4, "  Pozycja:      %2d/%2d   %2d/%2d   %2d/%2d    %2d/%2d", players[0].position.x, players[0].position.y, players[1].position.x, players[1].position.y, players[2].position.x, players[2].position.y, players[3].position.x, players[3].position.y);
    mvprintw(7, MAP_SIZE + 4, "  Smierci:      %4d     %4d    %4d     %4d", players[0].deaths, players[1].deaths, players[2].deaths, players[3].deaths);
    mvprintw(8, MAP_SIZE + 4, "Monetki");
    mvprintw(9, MAP_SIZE + 4, "  Przy sobie:   %4d   %4d   %4d   %4d", players[0].carried, players[1].carried, players[2].carried, players[3].carried);
    mvprintw(10, MAP_SIZE + 4, "  W banku:      %4d   %4d   %4d   %4d", players[0].budget, players[1].budget, players[2].budget, players[3].budget);

    mvprintw(13, MAP_SIZE + 4, "Legenda:");
    mvprintw(14, MAP_SIZE + 4, "1234 - gracze");
    mvprintw(15, MAP_SIZE + 4, "| - mur");
    mvprintw(16, MAP_SIZE + 4, "# - krzaki (2 tury na ich pokonanie)");
    mvprintw(17, MAP_SIZE + 4, "* - bestia");
    mvprintw(18, MAP_SIZE + 4, "c - moneta");
    mvprintw(19, MAP_SIZE + 4, "t - maly skarb (10 monet)");
    mvprintw(20, MAP_SIZE + 4, "T - duzy skarb (50 monet)");
    mvprintw(21, MAP_SIZE + 4, "A - obozowisko (z bankiem :P)");
    mvprintw(22, MAP_SIZE + 4, "D - upuszczony skarb");\

    mvprintw(24, MAP_SIZE + 4, "Obslugiwane przyciski:");
    mvprintw(25, MAP_SIZE + 4, "  B/b - dodanie bestii");
    mvprintw(26, MAP_SIZE + 4, "  c/t/T - dodanie odpowiedniego typu skarbu");
    mvprintw(27, MAP_SIZE + 4, "  R/r - reset gry, przy zachowaniu tych samych graczy i bestii");
    mvprintw(28, MAP_SIZE + 4, "        rozgrywka rozpocznie sie na nowej mapie z nowymi skarbami");
    mvprintw(29, MAP_SIZE + 4, "  Q/q - zamkniecie serwera i wszyskich polaczonych klientow");
    refresh();
}

void Serwer::drawBeastOnMap(Beast toput)
{
    *(*(map + toput.position.y) + toput.position.x) = '*';
}

void Serwer::colisionWithBeast(Beast &beast, Player &toReset)
{

    Ds newD(toReset.position.x, toReset.position.y, toReset.carried, toReset.charUnder);
    ds.push_back(newD);

    beast.position = toReset.position;
    beast.charUnder = 'D';
    if (toReset.charUnder == '#')
    {
        beast.inBush = true;
    }

    toReset.position = toReset.spawnPoint;
    toReset.carried = 0;
    toReset.deaths++;
}

void Serwer::colisionWithPlayer(Player &toReset1, Player &toReset2)
{
    Ds newD(toReset2.position.x, toReset2.position.y, toReset1.carried + toReset2.carried, toReset2.charUnder);
    ds.push_back(newD);

    *(*(map + toReset2.position.y) + toReset2.position.x) = 'D';

    toReset1.position = toReset1.spawnPoint;
    toReset1.carried = 0;
    toReset1.deaths++;

    toReset2.position = toReset2.spawnPoint;
    toReset2.carried = 0;
    toReset2.deaths++;
}

void Serwer::addTresure(char tres) //use only with 'c' 't' or 'T'
{
    while (1)
    {
        int i = rand() % MAP_SIZE;
        int j = rand() % MAP_SIZE;

        if (*(*(map + i) + j) == ' ')
        {
            *(*(map + i) + j) = tres;
            break;
        }
    }
}

void Serwer::addBeast()
{
    while (1)
    {
        int i = rand() % MAP_SIZE;
        int j = rand() % MAP_SIZE;

        if (*(*(map + i) + j) == ' ')
        {
            beasts.push_back(Beast(i, j));
            drawBeastOnMap(beasts[beasts.size() - 1]);
            break;
        }
    }
}

void Serwer::addPlayer(int number)
{
    while (1)
    {
        int i = rand() % MAP_SIZE;
        int j = rand() % MAP_SIZE;

        if (*(*(map + i) + j) == ' ')
        {
            players.push_back(Player(i, j, number));
            break;
        }
    }
}

void Serwer::drawPlayerOnMap(Player toput)
{
    if(toput.visible)
    {
        *(*(map + toput.position.y) + toput.position.x) = toput.number;
    }
    else
    {
        *(*(map + toput.position.y) + toput.position.x) = toput.charUnder;
    }
    
    
}

void Serwer::gameRestart()
{
    mapGenerate();

    for (int k = 0; k < players.size(); k++)
    {
        while (1)
        {
            int i = rand() % MAP_SIZE;
            int j = rand() % MAP_SIZE;

            if (*(*(map + i) + j) == ' ')
            {
                players[k].playerReset(i,j);
                break;
            }
        }
        drawPlayerOnMap(players[k]);
    }

    for (int k = 0; k < beasts.size(); k++)
    {
        while (1)
        {
            int i = rand() % MAP_SIZE;
            int j = rand() % MAP_SIZE;

            if (*(*(map + i) + j) == ' ')
            {
                beasts[k].position.x = i;
                beasts[k].position.y = i;
                beasts[k].charUnder = ' ';
                beasts[k].inBush = false;
                break;
            }
        }
        drawBeastOnMap(beasts[k]);
    }
    roundNumber=0;
}