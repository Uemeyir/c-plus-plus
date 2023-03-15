// Copyright 2022 Ümeyir Hallac

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "./GameOfLife.h"

// ___________________________________________________________________________________________
bool oldcells[MAX_SIZE][MAX_SIZE];
bool newcells[MAX_SIZE][MAX_SIZE];

bool (*pointerOld)[MAX_SIZE][MAX_SIZE];
bool (*pointerNew)[MAX_SIZE][MAX_SIZE];
// __________________________________________________________________________________________
int numRows;
int numCols;

//  _________________________________________________________________________________________
int glider[5][2] = { {1,0}, {2,1}, {0,2}, {1,2}, {2,2} };

//  _________________________________________________________________________________________
int numSteps;
int AliveCells;

int lastXClicked;
int lastYClicked;
//  _________________________________________________________________________________________
int row;
int col;

// __________________________________________________________________________________________
bool gameState;

// __________________________________________________________________________________________
int counterAliveCells = 0;

// ___________________________________________________________________________________________
void initTerminal() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);

  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
}

// _________________________________________________________________________________________
void showState() {
  for (int row = 0; row < MAX_SIZE; ++row) {
    for (int col = 0; col < MAX_SIZE; ++col) {
      attroff(A_REVERSE);
      if (oldcells[row][col]) {
        attron(A_REVERSE);
      }
      mvprintw(col, row * 2, "  ");
    }
  }
  attroff(A_REVERSE);

}

// _________________________________________________________________________________________
void initGame() {

  gameState = false;
  numSteps = 0;

  for (int row = 0; row < MAX_SIZE; ++row) {
    for (int col = 0; col < MAX_SIZE; ++col) {
      oldcells[row][col] = false;
      newcells[row][col] = false;
    }
  }
  
  pointerOld = &oldcells;
  pointerNew = &newcells;

  lastXClicked = -1;
  lastYClicked = -1;
  AliveCells = 0;
  
}

// ________________________________________________________________________________________
int numAliveNeighbors(int row, int col) {
  int counter = 0;
  // Check the 3x3 around the cell
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = col - 1; j <= col + 1; j++) {
      // Ignore the given cell
      if (i == row && j == col) {
        continue;
      }
      if (isLegalPos(i,j) && (*pointerNew)[i][j] == true) {
        counter++;
      }
    }
  }
  return counter;
}

// _______________________________________________________________________________________
bool processUserInput(int keycode) {
	MEVENT event;
	if (keycode == 113) {return false;} //  check if 'q' is pressed
	if (keycode == 32) {  //  if spacebar pressed pause or unpause the game
		gameState = !gameState;
	}
	if (keycode == 115) { // if 's' is pressed execute the next step
		updateState();
	}
	if (keycode == 99) { // if 'c' is pressed clear the game
	  for (int row = 0; row < MAX_SIZE; ++row) {
            for (int col = 0; col < MAX_SIZE; ++col) {
	      (*pointerNew)[row][col] = false;
	    }
	  }
	}
	if (keycode == 114) { // if 'r' is pressed fill random
	  for (int row = 0; row < MAX_SIZE; ++row) {
	    for (int col = 0; col < MAX_SIZE; ++col) {
	      (*pointerNew)[row][col] = (drand48() > 0.8) ? true : false;
	    }
	  }
	}
	if (keycode == 103) { // if 'g' is pressed -> generate glider
	  if (isLegalPos(lastXClicked, lastYClicked)){
	    (*pointerNew)[lastXClicked][lastYClicked] = false;
	    for (int i = 0; i < 5; ++i) {
	      int x = lastXClicked + glider[i][0];
	      int y = lastYClicked + glider[i][1];
	      (*pointerNew)[x][y] = isLegalPos(x,y) ? true : false;
	    }
	  }
	}
	if (KEY_MOUSE) {
	  if (getmouse(&event) == OK) {
	    if (event.bstate & BUTTON1_PRESSED) {
	      lastXClicked = event.x / 2;
	      lastYClicked = event.y;
	      if (isLegalPos(lastXClicked, lastYClicked)) {
	        if ((*pointerNew)[lastXClicked][lastYClicked]) {
		  (*pointerNew)[lastXClicked][lastYClicked] = false;
		} else {
		    (*pointerNew)[lastXClicked][lastYClicked] = true;
		} 
	      }
	    }
	  }
	}
	return true;
}

// ________________________________________________________________________________________
void updateState() {
	AliveCells = 0;

	bool (*tempGrid)[MAX_SIZE][MAX_SIZE] = pointerNew;
	pointerNew = pointerOld;
	pointerOld = tempGrid;

	for (int row = 0; row < MAX_SIZE; ++row) {
          for (int col = 0; col < MAX_SIZE; ++col) {
	    int neighbors = numAliveNeighbors(row,col);
	    (*pointerNew)[row][col] = false;
	    if ((*pointerOld)[row][col]) {
	      (*pointerNew)[row][col] = (neighbors > 1 && neighbors < 4) ? true : false;
	    } else if (neighbors == 3) {
	        (*pointerNew)[row][col] = true;
	    }
	    AliveCells += (*pointerNew)[row][col];
	  }
	}
	++numSteps;
}

// ________________________________________________________________________________________
bool isLegalPos(int x, int y) {
  if (x < MAX_SIZE && y < MAX_SIZE) {
    if (x >= 0 && y >= 0) {
      return true;
    }
  }
  return false;
}
