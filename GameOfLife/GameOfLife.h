// Copyright 2022 Ümeyir Hallac

#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

// The old state of all "cells"
const int MAX_SIZE = 1000;
extern bool oldcells[MAX_SIZE][MAX_SIZE];
extern bool newcells[MAX_SIZE][MAX_SIZE];

// pointer to oldcells and newcells
extern bool (*pointerOld)[MAX_SIZE][MAX_SIZE];
extern bool (*pointerNew)[MAX_SIZE][MAX_SIZE];

// coords of the last clicked cell
extern bool (*lastCoordsClicked)[MAX_SIZE][MAX_SIZE];

// counter for how many steps are done
extern int counter;

// counter for how many cells are alive
extern int counterAliveCells;

// bool to know if the game still running or not
extern bool gameState;

extern int lastXClicked;
extern int lastYClicked;

extern int AliveCells;

extern int counterAliveCells;
//  initialize the Terminal for ncurses
void initTerminal();

//  Initialize the game
void initGame();

//  current standings on the screen
void showState();

//  calculating the cells which are alive in given cell
int numAliveNeighbors(int row, int col);

//  processing the new state
void updateState();

// handeling the user input
bool processUserInput(int keycode);

// set the state the given cell alive. If "toggle" true invert the state
void setCell(int row, int col, bool toggle);

// put a glider at the given position
void putGlider(int row, int col);

// To check if the position is ok
bool isLegalPos(int x, int y);
#endif  //  GAMEOFLIFE_H_
