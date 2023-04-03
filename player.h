#ifndef _player_h_
#define _player_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <pthread.h>
#include <ncurses.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include "serwer.h"
#include "map.h"

enum direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STAY
};

class Point
{
public:
    int x;
    int y;
};

class Semaphore
{
public:
    sem_t *sem;
    char nameToUnlink[8];

    Semaphore()
    {
    }

    Semaphore(char *name, int startValue)
    {
        sem = sem_open(name, O_CREAT | O_EXCL, 0666, startValue);
        if (sem == NULL)
        {
            sem_unlink(name);
            sem = sem_open(name, O_CREAT, 0666, startValue);
        }
        memcpy(nameToUnlink, name, 8);
    }

    ~Semaphore()
    {
        sem_unlink(nameToUnlink);
    }

    Semaphore(const Semaphore &sem) = delete;
    Semaphore(Semaphore &&sem) //important for vector
    {
        this->sem = sem.sem;
        sem.sem = NULL;
        memcpy(nameToUnlink, sem.nameToUnlink, 8);
        *sem.nameToUnlink = '\0';
    }

    void post()
    {
        sem_post(sem);
    }
    void wait()
    {
        sem_wait(sem);
    }
    int trywait() //if -1 no response
    {
        int ret = sem_trywait(sem);
        return ret;
    }
};

class Player
{
public:
    pid_t PID;
    pid_t serwerPID;
    Point position;
    enum type
    {
        HUMAN,
        CPU
    } humanOrCPU;
    int carried;
    int budget;
    int deaths;
    Point spawnPoint;
    bool inBush;
    char charUnder;
    char number;
    enum direction dir;
    char pieceOfMap[MAP_SIZE][MAP_SIZE + 3];
    bool exit;
    long roundNumber;
    bool visible; //could be connected

    Player(int x, int y, int num)
    {
        spawnPoint.x = x;
        spawnPoint.y = y;
        position.x = x;
        position.y = y;
        carried = 0;
        budget = 0;
        deaths = 0;
        inBush = false;
        charUnder = ' ';
        number = num + '1';
        PID = -1;
        serwerPID = getpid();
        humanOrCPU = HUMAN;
        exit = false;
        roundNumber = 0;
        visible = true;
    }

    Player(const Player &ply)
    {
        spawnPoint.x = ply.spawnPoint.x;
        spawnPoint.y = ply.spawnPoint.y;
        position.x = ply.position.x;
        position.y = ply.position.y;
        carried = ply.carried;
        budget = ply.budget;
        deaths = ply.deaths;
        inBush = ply.inBush;
        charUnder = ply.charUnder;
        number = ply.number;
        PID = ply.PID;
        serwerPID = ply.serwerPID;
        humanOrCPU = ply.humanOrCPU;
        dir = ply.dir;
        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE + 1; j++)
            {
                pieceOfMap[i][j] = ply.pieceOfMap[i][j];
            }
        }
        roundNumber = ply.roundNumber;
        exit = ply.exit;
        visible = ply.visible;
    }
    Player(Player &&ply) //important for vector
    {
        spawnPoint.x = ply.spawnPoint.x;
        spawnPoint.y = ply.spawnPoint.y;
        position.x = ply.position.x;
        position.y = ply.position.y;
        carried = ply.carried;
        budget = ply.budget;
        deaths = ply.deaths;
        inBush = ply.inBush;
        charUnder = ply.charUnder;
        number = ply.number;
        PID = ply.PID;
        serwerPID = ply.serwerPID;
        humanOrCPU = ply.humanOrCPU;
        dir = ply.dir;
        roundNumber = ply.roundNumber;
        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE + 1; j++)
            {
                pieceOfMap[i][j] = ply.pieceOfMap[i][j];
            }
        }
        exit = ply.exit;
        visible = ply.visible;
    }

    void playerToPlayerCopy(Player *dest, long roundNum)
    {
        dest->spawnPoint = spawnPoint;
        dest->position = position;
        dest->humanOrCPU = humanOrCPU;
        dest->carried = carried;
        dest->budget = budget;
        dest->deaths = deaths;
        dest->inBush = inBush;
        dest->charUnder = charUnder;
        dest->number = number;
        dest->roundNumber = roundNum;

        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE + 1; j++)
            {
                dest->pieceOfMap[i][j] = pieceOfMap[i][j];
            }
        }
    }

    void playerReset(int x, int y)
    {
        spawnPoint.x = x;
        spawnPoint.y = y;
        position.x = x;
        position.y = y;
        carried = 0;
        budget = 0;
        deaths = 0;
        inBush = false;
        charUnder = ' ';
        humanOrCPU = HUMAN;
        exit = false;
        roundNumber = 0;
    }
};

#endif