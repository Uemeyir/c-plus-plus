// Copyright 2022 Ümeyir Hallac

#include <ncurses.h>
#include <unistd.h>
#include "./GameOfLife.h"

int main() {
  initTerminal();
  initGame();

  while (processUserInput(getch())) {
    if (gameState) {
      updateState();
    }
    // draw and wait
    showState();
    usleep(50'000);
  }
  endwin();
}
