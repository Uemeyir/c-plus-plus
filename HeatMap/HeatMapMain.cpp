#include <unistd.h>
#include <string>
#include <iostream>
#include "./TerminalManager.h"
#include "./HeatMap.h"

int main(int argc, char** argv) {
  // Parse the command-line arguemnts
  if (argc != 2) {
    std::cout << "You have to add a file" << std::endl;
    std::exit(1);
  }

  TerminalManager tm;
  HeatMap heatMap;
  const size_t numRows = tm.numRows();
  const size_t numCols = tm.numCols();

  std::string filename = argv[1];

  heatMap.readPointsFromFile(filename);
  heatMap.computeHeatMap(numRows, numCols);
  heatMap.drawHeatMap(&tm);
  tm.refresh();
  while (tm.getUserInput().keycode_ != 'q') {
    usleep(100'000);
  }
}
