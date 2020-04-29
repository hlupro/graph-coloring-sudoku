
#include "graph.h"

int main() {
  // std::cout << "===========GRAPH_COLORING AND SUDOKU=================" << std::endl;
  //
  int sudokuGrid = 9;
  //
  // std::cout << "4x4 or 9x9?" << std::endl;
  // std::cin>> sudokuGrid;
  //
  Graph sudoku(sudokuGrid);
  //
  sudoku.print();

}
