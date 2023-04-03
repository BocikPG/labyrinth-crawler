
#include "player.h"

void Player::copyToPlayer(Player *toCopy)
{
    position = toCopy->position;
    humanOrCPU = toCopy->humanOrCPU;
    carried = toCopy->carried;
    budget = toCopy->budget;
    deaths = toCopy->deaths;
    spawnPoint = toCopy->spawnPoint;
    inBush = toCopy->inBush;
    charUnder = toCopy->charUnder;
    number = toCopy->number;
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE + 1; j++)
        {
            pieceOfMap[i][j] = toCopy->pieceOfMap[i][j];
        }
    }
    exit = toCopy->exit;
    roundNumber = toCopy->roundNumber;
}

void Player::copyToShMemory(Player *toCopy)
{
    toCopy->dir = dir;
}

void Player::mapDisplay()
{
    for (int k = 0; k < MAP_SIZE; k++)
    {
        for (int l = 0; l < MAP_SIZE; l++)
        {
            mvprintw(l, k, "%c", pieceOfMap[l][k]);
        }
    }

    mvprintw(0, MAP_SIZE + 4, "PID Serwera: %5d", PID);
    mvprintw(1, MAP_SIZE + 4, "Numer tury: %5d", roundNumber);

    mvprintw(3, MAP_SIZE + 4, "Gracz:");
    mvprintw(4, MAP_SIZE + 4, "  Numer:          %c", number);
    mvprintw(5, MAP_SIZE + 4, "  Typ:          %s", "HUMAN"); //players[0].humanOrCPU
    mvprintw(6, MAP_SIZE + 4, "  Pozycja:      %2d/%2d", position.x, position.y);
    mvprintw(7, MAP_SIZE + 4, "  Smierci:      %2d", deaths);
    mvprintw(8, MAP_SIZE + 4, "Monetki");
    mvprintw(9, MAP_SIZE + 4, "  Przy sobie:   %4d", carried);
    mvprintw(10, MAP_SIZE + 4, "  W banku:     %4d", budget);

    mvprintw(13, MAP_SIZE + 4, "Legenda:");
    mvprintw(14, MAP_SIZE + 4, "1234 - gracze");
    mvprintw(15, MAP_SIZE + 4, "| - mur");
    mvprintw(16, MAP_SIZE + 4, "# - krzaki (2 tury na ich pokonanie)");
    mvprintw(17, MAP_SIZE + 4, "* - bestia");
    mvprintw(18, MAP_SIZE + 4, "c - moneta");
    mvprintw(19, MAP_SIZE + 4, "t - maly skarb (10 monet)");
    mvprintw(20, MAP_SIZE + 4, "T - duzy skarb (50 monet)");
    mvprintw(21, MAP_SIZE + 4, "A - obozowisko (z bankiem :P)");
    mvprintw(22, MAP_SIZE + 4, "D - upuszczony skarb");



    refresh();
}