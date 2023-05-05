// Copyright 2022 Uemeyir Hallac

#include <ncurses.h>
#include "./Snake.h"

// ____________________________________________________________________________
// Global variables. See the header for documentation.

// change the variables look in internet for command
int snakeX[LENGTH];
int snakeY[LENGTH];

int positionX;
int positionY;
int newpositionX;
int newpositionY;

int screenPixelsX;
int screenPixelsY;


// ____________________________________________________________________________
void initTerminal() {
  initscr();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  cbreak();
  noecho();

  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLUE);
  init_pair(2, COLOR_RED, COLOR_CYAN);

  // COLS and LINES are global variables from ncurses (dimensions of screen).
  screenPixelsX = COLS / pixelSizeWidth;
  screenPixelsY = LINES / pixelSizeHeight;
}

// ____________________________________________________________________________
void initSnake() {
  for (int i = 0; i < LENGTH; i++) {
    snakeX[i] = LENGTH - i;
    snakeY[i] = screenPixelsY / 2;
  }

  positionX = 1;
  positionY = 0;
  newpositionX = positionX;
  newpositionY = positionY;
}

// _____________________________________________________________________________
void drawPixel(int y, int x) {
  for (int i = 0; i < pixelSizeHeight; i++) {
    for (int j = 0; j < pixelSizeWidth; j++) {
      mvprintw(y * pixelSizeHeight + i, x * pixelSizeWidth + j, " ");
    }
  }
}

// ____________________________________________________________________________
void drawBorder() {
  attron(COLOR_PAIR(1));
  attron(A_REVERSE);
  for (int y = 0; y < screenPixelsY; y++) {
    for (int x = 0; x < screenPixelsX; x++) {
      if (y == 0 || y == screenPixelsY - 1 || x == 0 || x == screenPixelsX - 1) {
        drawPixel(y, x);
      }
    }
  }

  attroff(A_REVERSE);
  attroff(COLOR_PAIR(1));
}

// ____________________________________________________________________________
void drawSnake(bool show) {
  if (show == true) attron(A_REVERSE);
  for (int i = 1; i < LENGTH; i++) {
    drawPixel(snakeY[i], snakeX[i]);
  }

  attron(COLOR_PAIR(2));
  drawPixel(snakeY[0], snakeX[0]);
  attroff(COLOR_PAIR(2));

  attroff(A_REVERSE);
}
// _____________________________________________________________________________________________
bool collidesWithBorder() {
  if (snakeX[0] <= 0 || snakeX[0] >= screenPixelsX - 1 || 
      snakeY[0] <= 0 || snakeY[0] >= screenPixelsY - 1) {
    return true;
  } else {
    return false;
  }
}

// ____________________________________________________________________________
bool collidesWithSelf() {
  int storeHeadX = snakeX[0];
  int storeHeadY = snakeY[0];

  for (int i = 1; i < LENGTH; i++) {
    if (storeHeadX == snakeX[i] && storeHeadY == snakeY[i]) {
      return true;
    }
  }
  return false;
}

// ____________________________________________________________________________
void moveSnake() {
  int newPosX = snakeX[0] + positionX;
  int newPosY = snakeY[0] + positionY;

  for (int i = LENGTH - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  snakeX[0] = newPosX;
  snakeY[0] = newPosY;

  if (newpositionX + positionX != 0 || newpositionY + positionY != 0) {
    positionX = newpositionX;
    positionY = newpositionY;
  }
}

// ____________________________________________________________________________
bool handleKey(int key) {
  if (key == 27) return false;
  if (key == KEY_UP) {
    newpositionX = 0;
    newpositionY = -1;
  }
  if (key == KEY_DOWN) {
    newpositionX = 0;
    newpositionY = 1;
  }
  if (key == KEY_LEFT) {
    newpositionX = -1;
    newpositionY = 0;
  }
  if (key == KEY_RIGHT) {
    newpositionX = 1;
    newpositionY = 0;
  }

  return true;
}
