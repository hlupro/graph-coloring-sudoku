
#include "graph.h"

int main() {
  // std::cout << "===========GRAPH_COLORING AND SUDOKU=================" << std::endl;
  //
  //int sudokuGrid = 9;
  //
  // std::cout << "4x4 or 9x9?" << std::endl;
  // std::cin>> sudokuGrid;
  //
  // std::cout << "4x4 Sudoku Board" << std::endl;
  // Graph sudoku(4);
  // sudoku.ColorGreedy();
  // sudoku.print();
  // sudoku.printBoard();
  // std::cout << std::endl;
  std::cout << "9x9 Sudoku Board" << std::endl;
  Graph sudoku2(9);
  sudoku2.hardHint();
  sudoku2.addUnknowns();
  sudoku2.ColorBackTrack();
  //sudoku2.ColorGreedy();

  sudoku2.printBoard();

}
