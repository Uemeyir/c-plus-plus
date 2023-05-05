// Copyright 2022, Uemeyir Hallac

#ifndef TERMINALMANAGER_H_
#define TERMINALMANAGER_H_

#include <cstddef>

// Class for the input from the user.
class UserInput {
  public:
  // The code of the key pressed.
  int keycode_;
};

// A class managing the input and output via the terminal, using ncurses.
class TerminalManager {
 public:
  // Constructor: initialize the terminal for use with ncurses.
  TerminalManager();

  // Destructor: Clean up the screen.
  ~TerminalManager();

  // Get input from the user.
  UserInput getUserInput();

  // Draw a "pixel" at the given position and with the given intensity between
  // The intensity has to be in [0.0, 1.0]
  void drawPixel(int row, int col, bool inverse, float intensity);

  // Refresh the screen.
  void refresh();

  // Get the dimensions of the screen.
  int numRows() const { return numRows_; }
  int numCols() const { return numCols_; }

  // Get the number of colors.
  int numColors();

 private:
  // The number of "logical" rows and columns of the screen.
  int numRows_;
  int numCols_;

  // Convert an intensity in the range [0.0, 1.0] to the index of the
  // corresponding color
  size_t convertIntensityToColor(float intensity) const;
};

#endif  // TERMINALMANAGER_H_
