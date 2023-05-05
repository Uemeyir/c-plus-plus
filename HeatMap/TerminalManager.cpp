// Copyright 2022, Uemeyir Hallac

#include "./TerminalManager.h"
#include <ncurses.h>

#include <algorithm>
#include <cmath>
#include <stdexcept>

static constexpr size_t systemColors = 16;

// _____________________________________________________________
size_t TerminalManager::convertIntensityToColor(float intensity) const {
    // Scale the intensity value to the range [0, 1000]
    intensity = std::round(std::clamp(intensity, 0.0f, 1.0f) * 1000.0f);
    // Compute the color index based on the scaled intensity value
    if (intensity <= 333) {
        return systemColors + (intensity * 2) / 333;
    } else if (intensity <= 666) {
        return systemColors + 2 + ((intensity - 333) * 4) / 333;
    } else {
        return systemColors + 6 + ((intensity - 666) * 8) / 334;
    }
}


// ____________________________________________________________________________
TerminalManager::TerminalManager() {
  initscr();
  start_color();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  // Catch mouse events
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
  start_color();

  if (COLORS < 200) {
    endwin();
  }

  // Define color
  for (int color = systemColors; color < COLORS; ++color) {
    int intensity = color / (COLORS - systemColors);
    init_color(color, intensity, 0, 0);
    init_pair(color, color, 0);
  }
  init_pair(0, COLOR_RED, COLOR_GREEN);
  numRows_ = LINES;
  numCols_ = COLS / 2;
}

// ____________________________________________________________________________
TerminalManager::~TerminalManager() { endwin();}

// ____________________________________________________________________________
void TerminalManager::drawPixel(int row, int col,
                                bool inverse, float intensity) {
  int color = convertIntensityToColor(intensity);
  if (inverse) attron(A_REVERSE);
  attron(COLOR_PAIR(color));
  mvprintw(row, 2 * col, "  ");
  attroff(COLOR_PAIR(color));
  if (inverse) attroff(A_REVERSE);
}

// ____________________________________________________________________________
void TerminalManager::refresh() {
  ::refresh();
}

// ___________________________________________________________________________
UserInput TerminalManager::getUserInput() {
  UserInput userInput;
  userInput.keycode_ = getch();
  return userInput;
}

// ___________________________________________________________________________
int TerminalManager::numColors() {
  return COLORS;
}
