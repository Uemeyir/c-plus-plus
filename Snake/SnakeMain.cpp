// Copyright 2022 Uemeyir Hallac

#include <unistd.h>
#include <ncurses.h>
#include "./Snake.h"

// Speed in pixel per hour.
int speed = 3600;
// Acceleration in pixel per hour squared.
int acceleration = 3600;

// Main function.
int main() {
  initTerminal();
  initSnake();
  drawBorder();
  drawSnake(true);
  refresh();

  while (true) {
    for (int i = 0; i < 3600 * 1000 / speed; i++) {
      if (!handleKey(getch())) {
        endwin();
        return 0;
      }
      usleep(1000);
    }
    speed += acceleration * 3600 / speed;
    drawSnake(false);
    moveSnake();
    drawSnake(true);
    refresh();
    if (collidesWithBorder() || collidesWithSelf()) {
      // Game over, wait for the escape key to be pressed.
      while (handleKey(getch())) {}
      endwin();
      return 0;
    }
  }
}
