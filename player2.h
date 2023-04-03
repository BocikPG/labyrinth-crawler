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
#include <unistd.h>
#include <fcntl.h>

#define MAP_SIZE 36

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
    char *nameToUnlink;

    Semaphore()
    {
    }

    Semaphore(char *name)
    {
        sem = sem_open(name, 0);
        nameToUnlink = name;
    }

    ~Semaphore()
    {
        sem_unlink(nameToUnlink);
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

    Player(Player *toCopy)
    {
        PID = getpid();
        serwerPID = toCopy->serwerPID;
        position = toCopy->position;
        humanOrCPU = toCopy->humanOrCPU;
        carried = toCopy->carried;
        budget = toCopy->budget;
        deaths = toCopy->deaths;
        spawnPoint = toCopy->spawnPoint;
        inBush = toCopy->inBush;
        charUnder = toCopy->charUnder;
        number = toCopy->number;
        exit=false;
        roundNumber = toCopy->roundNumber;
    }

    void copyToPlayer(Player *toCopy);
    void copyToShMemory(Player *toCopy);
    void mapDisplay();
};

#endif