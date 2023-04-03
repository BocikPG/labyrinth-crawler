#ifndef _serwer_h_
#define _serwer_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <pthread.h>
#include <ncurses.h>

#include "player.h"
#include "map.h"

class Ds
{
public:
    Point position;
    int value;
    char charUnder;

    Ds(int x, int y, int valueToAssign, char charUnderToAssign)
    {
        position.x = x;
        position.y = y;
        value = valueToAssign;
        charUnder = charUnderToAssign;
    }
};

class Beast
{

public:
    pthread_t th;
    bool inBush;
    char charUnder;
    Point position;
    enum direction dir;
    char pieceOfMap[MAP_SIZE][MAP_SIZE+3];

    Beast(int x, int y)
    {
        inBush = false;
        charUnder = ' ';
        position.x = x;
        position.y = y;
    }

    static void *makeARequestToMoveThread(void *beastIGuess);
};

class Serwer
{
public:
    char **map;
    std::vector<Beast> beasts;
    std::vector<Player> players;
    std::vector<Ds> ds;
    std::vector<Semaphore> semaphors;
    std::vector<Player *> shmPointers;
    pid_t PID;
    long roundNumber;

    Serwer()
    {
        beasts.clear();
        players.clear();
        ds.clear();
        roundNumber=0;
        PID = getpid();
    }

    void createPieceOfMap(Point position, char pieceOfMap[MAP_SIZE][MAP_SIZE+3]);

    void mapGenerate();
    void mapDisplay();

    void addBeast();
    void drawBeastOnMap(Beast toput);
    void colisionWithBeast(Beast &beast, Player &toReset);
    void actualMoveBeast(Beast &toMove);

    void addPlayer(int number);
    void drawPlayerOnMap(Player toput);
    void colisionWithPlayer(Player &toReset1, Player &toReset2);
    void actualMovePlayer(Player &toMove, enum direction dir);

    void addTresure(char tres);

    void gameRestart();

    void endGame();
};

#endif