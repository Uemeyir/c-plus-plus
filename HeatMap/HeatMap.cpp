// Copyright 2022, Uemeyir Hallac

#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <fstream>
#include "./HeatMap.h"

// ____________________________________________________________________________
void HeatMap::readPointsFromFile(const std::string &filename) {
  std::ifstream filePoints(filename);
  std::string line;
  while (std::getline(filePoints, line)) {
    // after  getPoints implement use it here
    points_.push_back(getPoints(line));
  }
}

// ____________________________________________________________________________
Point HeatMap::getPoints(const std::string &input) {
  size_t position1 = input.find('(');
  size_t position2 = input.find(' ');
  size_t position3 = input.find(')');

  std::string firstNumb = input.substr(position1 + 1, position2 - position1 - 2);
  std::string secondNumb = input.substr(position2 + 1, position3 - position2 - 1);

  float firstNumber = std::stof(firstNumb);
  float secondNumber = std::stof(secondNumb);
  return Point{std::make_pair(firstNumber, secondNumber)};
}

// ____________________________________________________________________________
void HeatMap::computeHeatMap(size_t numRows, size_t numCols) {
  float minLng = points_[0].coordinates_.first;
  float maxLng = points_[0].coordinates_.first;

  for (const auto& point : points_) {
    if (point.coordinates_.first < minLng) {
      minLng = point.coordinates_.first;
    }
    if (point.coordinates_.first > maxLng) {
      maxLng = point.coordinates_.first;
    }
  } 

  float minLat = points_[0].coordinates_.second;
  float maxLat = points_[0].coordinates_.second;

  for (const auto& point : points_) {
    if (point.coordinates_.second < minLat) {
      minLat = point.coordinates_.second;
    }
    if (point.coordinates_.second > maxLat) {
      maxLat = point.coordinates_.second;
    }
  }
 
  // wenns klappt noch ändern
  float rowScaling = numRows / (maxLat - minLat);
  float colScaling = numRows / (maxLng - minLng);

  float scaling = std::min(rowScaling, colScaling);

  // One of the coordinates will not cover the screen, compute an offset s.t.
  // the map is centered.
  size_t colOffset = (numCols - (maxLng - minLng) * scaling) / 2;
  size_t rowOffset = (numRows - (maxLat - minLat) * scaling) / 2;

  for (const Point& point : points_) {
    // Compute to which row and column the point will be mapped.
    size_t row = (point.coordinates_.second - minLat) * scaling + rowOffset;
    size_t col = (point.coordinates_.first - minLng) * scaling +  colOffset;
    // The points that ligh exactly on the highest latitude or longitude
    // have a row or column index that is too high now, map them back to the
    // highest row/ column.
    if (row >= numRows) row = numRows - 1;
    if (col >= numCols) col = numCols - 1;
    // Latitudes grow from south to north but rows from top to bottom.
    // Invert the row index s.t. the countries are not displayed upside down.
    row = numRows - 1 - row;
    // Add an entry for the heat map of the cell for this point.
    heatMap_[Cell{row, col}]++;
  }
}

// ____________________________________________________________________________
void HeatMap::drawHeatMap(TerminalManager* tm) {
if (heatMap_.empty()) return;

  // First compute the maximum number of points in a cell.
  // This will be used to compute the intensity between 0 and 1.
  size_t maxCellCount = 0;
  for (const auto& cellAndCount : heatMap_) {
     auto count = cellAndCount.second;
     maxCellCount = std::max(count, maxCellCount);
  }

  for (const auto& [cell, count] : heatMap_) {
     float intensity = 1.0 * count / maxCellCount;
     tm->drawPixel(cell.row_, cell.col_, true, intensity);
  }
  tm->refresh();
}
