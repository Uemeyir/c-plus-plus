// Copyright 2022, Uemeyir Hallac

#ifndef SNAKE_H_
#define SNAKE_H_

// The total number of logical pixels on the screen.
extern int screenPixelsX;
extern int screenPixelsY;

// To get a square 
const int pixelSizeWidth = 2;
const int pixelSizeHeight = 1;


const int LENGTH = 13;

// The positions of the segments of the snake in pixels. At index 0 there is
// the head and at index SNAKE_LENGTH - 1 there is the tail.
extern int  snakeX[LENGTH];
extern int  snakeY[LENGTH];


extern int positionX;
extern int positionY;

extern int newpositionX;
extern int newpositionY;

// ___________________________________________________________________________

// Initialize the terminal for use with ncurses commands.
void initTerminal();

// Initialize the snake.
void initSnake();

// Draw a pixel at the position given by y and x. Note that a pixel consists of
// multiple space characters, depending on `pixelWidth` and `pixelHeight`.
void drawPixel(int y, int x);

// Draw the snake (show == true: draws in black, show == true: draws in white).
void drawSnake(bool show);

// Draw a border around the screen.
void drawBorder();


// Return true iff the head of the snake is on our out of the border
bool collidesWithBorder();

// Return true iff the head of the snake is on the same pixel as another segment
// of the snake.
bool collidesWithSelf();

// Update the position of the  snake when `milliseconds` have passed since the
// last call to `moveSnake`
void moveSnake();

// Update the direction and the speed of the snake given the last pressed key.
// Return false if `escape` was pressed, return true for any other key.
bool handleKey(int key);

#endif  // SNAKE_H_
