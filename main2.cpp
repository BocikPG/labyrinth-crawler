#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <ncurses.h>
#include <sys/types.h>
#include <signal.h>

#include "player.h"

int main(void)
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);
    timeout(500);
    keypad(stdscr, TRUE);

    Semaphore join("joinGame");
    if (join.sem == NULL)
    {
        printw("Nie można się połączyć z serwerem, wciśnij cokolwiek żeby kontynuować");
        refresh();
        getchar();
        return 1;
    }

    join.post();

    int fdJoin = shm_open("joinShm", O_RDWR, 0666);
    int *joinShm = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fdJoin, 0);

    napms(1000);
    join.wait();

    if (*joinShm >= 4)
    {
        printw("Nie mozna dolaczyc - limit graczy osiagniety");
        refresh();
        getchar();
        return 2;
    }

    int myNumber = *(joinShm);

    char name[8];
    snprintf(name, 8, "%s%d\0", "player", myNumber + 1); //tworzy nazwę player1, player2...

    Semaphore communicateWithSerwer(name);

    int fd = shm_open(name, O_RDWR, 0666);
    Player *shMemory = (Player *)mmap(NULL, sizeof(Player), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    Player me(shMemory);

    shMemory->PID = me.PID;

    communicateWithSerwer.post();

    printw("Oczekiwanie na pozostalych graczy");
    refresh();
    napms(1000);
    communicateWithSerwer.wait();

    while (1)
    {

        me.copyToPlayer(shMemory);
        me.mapDisplay();
        int choice = getch();
        switch (choice)
        {
        case KEY_UP:
            shMemory->dir = UP;
            communicateWithSerwer.post();
            break;
        case KEY_DOWN:
            shMemory->dir = DOWN;
            communicateWithSerwer.post();
            break;
        case KEY_LEFT:
            shMemory->dir = LEFT;
            communicateWithSerwer.post();
            break;
        case KEY_RIGHT:
            shMemory->dir = RIGHT;
            communicateWithSerwer.post();
            break;
        case 'q':
            me.exit = true;
            break;
        case 'Q':
            me.exit = true;
            break;

        default:
            break;
        }
        if (me.exit)
        {
            break;
        }

        if (kill(me.serwerPID, 0) != 0)
        {
            mvprintw((MAP_SIZE) / 2, (MAP_SIZE) / 2, "Utracono polaczenie z serwerem... Zamykanie...");
            refresh();
            napms(3000);

            shm_unlink(name);
            endwin();
            return 3;
        }
        communicateWithSerwer.wait();
    }

    shm_unlink(name);
    endwin();
    return 0;
}
