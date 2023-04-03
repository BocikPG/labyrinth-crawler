#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <ncurses.h>
#include <sys/types.h>
#include <signal.h>

#include "map.h"
#include "serwer.h"

int main(void) //game loop: move beast, move players
{
    initscr();
    printw("oczekiwanie na graczy...");
    refresh();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);
    timeout(100);

    Serwer dane;
    dane.mapGenerate();

    Semaphore join("joinGame", 0);
    int fd = shm_open("joinShm", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(int));
    int *joinShm = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    for (int i = 0; i < 4; i++)
    {
        join.wait();

        *(joinShm) = i;

        char name[8];
        snprintf(name, 8, "%s%d\0", "player", i + 1); //tworzy nazwę player1, player2...

        dane.addPlayer(i);

        dane.semaphors.push_back(std::move(Semaphore(name, 0)));

        //creating shared memory, pointer to it is in shmPointers[i]
        int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
        ftruncate(fd, sizeof(Player) + 36 * sizeof(char *) + 36 * 36 * sizeof(char));
        dane.shmPointers.push_back((Player *)mmap(NULL, sizeof(Player), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
        dane.players[i].playerToPlayerCopy(dane.shmPointers[i], dane.roundNumber); //map is trash until the game starts

        join.post();

        dane.semaphors[i].wait();

        dane.players[i].PID = dane.shmPointers[i]->PID;
        dane.drawPlayerOnMap(dane.players[i]);
    }

    *joinShm = 7;

    //all players added

    dane.addBeast();

    dane.mapDisplay();

    while (1) //game loop
    {
        if (join.trywait() == 0) //for more players
        {
            join.post();
        }

        for (int i = 0; i < dane.beasts.size(); i++)
        {
            dane.createPieceOfMap(dane.beasts[i].position, dane.beasts[i].pieceOfMap);
            pthread_create(&dane.beasts[i].th, NULL, dane.beasts[i].makeARequestToMoveThread, &dane.beasts[i]);
        }

        for (int i = 0; i < dane.players.size(); i++)
        {
            if (kill(dane.players[i].PID, 0) != 0)
            {
                dane.players[i].visible = false;
                dane.drawPlayerOnMap(dane.players[i]); //hiding disconnected player
            }

            dane.createPieceOfMap(dane.players[i].position, dane.players[i].pieceOfMap);
            dane.players[i].playerToPlayerCopy(dane.shmPointers[i], dane.roundNumber);
            dane.semaphors[i].post();
        }

        if (dane.players[0].visible == false && dane.players[1].visible == false && dane.players[2].visible == false && dane.players[3].visible == false)
        {
            mvprintw((MAP_SIZE)/2, (MAP_SIZE)/2, "Wszyscy gracze rozlaczyli sie... Zamykanie...");
            refresh();

            napms(3000); //waiting just to inform

            for (int i = 0; i < 4; i++)
            {
                char name[8];
                snprintf(name, 8, "%s%d", "player", i + 1); //tworzy nazwę player1, player2...

                shm_unlink(name);
            }
            shm_unlink("joinShm");

            endwin();
            return 1;
        }

        dane.mapDisplay();
        napms(500); //time to make a decision to move

        for (int i = 0; i < dane.beasts.size(); i++)
        {
            pthread_join(dane.beasts[i].th, NULL);
            dane.actualMoveBeast(dane.beasts[i]);
        }

        for (int i = 0; i < dane.players.size(); i++)
        {
            int trySem = dane.semaphors[i].trywait();
            if (trySem == 0) //if semaphore posted -> move
            {
                dane.players[i].PID = dane.shmPointers[i]->PID;
                dane.actualMovePlayer(dane.players[i], dane.shmPointers[i]->dir);
            }
        }
        dane.roundNumber++;

        bool exit = false;
        int choice = getch();
        switch (choice)
        {
        case 'b':
        case 'B':
            dane.addBeast();
            break;
        case 'c':
            dane.addTresure('c');
            break;
        case 't':
            dane.addTresure('t');
            break;
        case 'T':
            dane.addTresure('T');
            break;
        case 'r':
        case 'R':
            dane.gameRestart();
            break;
        case 'q':
        case 'Q':
            exit = true;
            for (int i = 0; i < dane.shmPointers.size(); i++)
            {
                dane.shmPointers[i]->exit = true;
                dane.semaphors[i].post();
            }
            break;
        }
        if (exit)
        {
            break;
        }
    }

    mvprintw(13, (MAP_SIZE) / 2, "Zamykanie...");
    refresh();

    napms(2000); //waiting for clients to close

    for (int i = 0; i < 4; i++)
    {
        char name[8];
        snprintf(name, 8, "%s%d", "player", i + 1); //tworzy nazwę player1, player2...

        shm_unlink(name);
    }
    shm_unlink("joinShm");

    endwin();
    return 0;
}
