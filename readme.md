# Labyrinth-crawler

It's project of mine done in early 2022 for linux console.

The game comes with server and client (which can be run multiple times for multiplayer).

## Server

Server synchronizes player movements, moves the beast (an enemy), and generates map (on start of the game or on command).

## Client

Player can move around, but never sees more than 2 blocks away from him. He can also collect treasures and hide them at the campfire. At the meeting with the beast, the player dies, and drops all collected (and not stored) treasures.

## Tech

I'm using pointers, semaphores, threads (to control beasts) and few object functions.

To display the ncurses library was used.