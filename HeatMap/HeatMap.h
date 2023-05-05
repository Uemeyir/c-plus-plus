// Copyright 2022, Uemeyir Hallac

#include <vector>
#include <string>
#include <unordered_map>
#include "./TerminalManager.h"

class Point {
  public:
    Point(std::pair<float, float> coordinates) : coordinates_(coordinates) {}
    std::pair<float,float> coordinates_;
};

// A 2D cell with size_t coordinates.
class Cell {
 public:
  size_t row_;
  size_t col_;
  // To store the Cells in a hashMap we have
  // to define the equality == between Cells.
  bool operator==(const Cell& other) const {
    return row_ == other.row_ && col_ == other.col_;
  }
};

// We use Cell as the key type to a hash map, so we have to define
// a hash function
template<>
struct std::hash<Cell> {
  size_t operator()(const Cell& p) const {
    auto hash1 = std::hash<size_t>{}(p.row_);
    auto hash2 = std::hash<size_t>{}(p.col_);
    if (hash1 != hash2) {
      return hash1 ^ hash2;
    }
    // If hash1 == hash2, their XOR is zero.
    return hash1;
  }
};

class HeatMap {
  public:
    // reads the points from the tsv file nad store it to Point
    void readPointsFromFile(const std::string &filename);

    // gets the point from the string
    Point getPoints(const std::string &input);

    // Computes the point for the map
    void computeHeatMap(size_t numRows, size_t numCols);

    // Draws the heatmap
    void drawHeatMap(TerminalManager* tm);
    

  private:
    std::vector<Point> points_;
    using CellToCountMap = std::unordered_map<Cell, size_t>;
    CellToCountMap heatMap_;
};
