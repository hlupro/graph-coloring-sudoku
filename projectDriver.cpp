
#include "graph.h"

int main() {
  // std::cout << "===========GRAPH_COLORING SUDOKU APPLICATION=================" << std::endl;
  //
  //
  //
  //
  std::cout << "\nEasy Difficulty Sudoku Board" << std::endl;
  Graph sudoku(9);
  sudoku.easyHint();
  std::cout << "Number of Hints: " << sudoku.numHints() << std::endl;
  sudoku.printBoard();
  auto start = std::chrono::system_clock::now();
  sudoku.ColorBackTrack();
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elasped_seconds = end-start;
  //sudoku2.ColorGreedy();
  std::cout << "Solution" << std::endl;
  sudoku.printBoard();
  std::cout << "Solution found in " << std::fixed << elasped_seconds.count() << " seconds\n" << std::endl;

  std::cout << "Intermediate Difficulty Sudoku Board" << std::endl;
  Graph sudoku2(9);
  sudoku2.intermediateHint();
  std::cout << "Number of Hints: " << sudoku.numHints() << std::endl;
  sudoku2.printBoard();
  start = std::chrono::system_clock::now();
  sudoku2.ColorBackTrack();
  end = std::chrono::system_clock::now();
  elasped_seconds = end-start;
  std::cout << "Solution" << std::endl;
  sudoku2.printBoard();
  std::cout << "Solution found in " << std::fixed << elasped_seconds.count() << " seconds\n" << std::endl;

  std::cout << "Hard Difficulty Sudoku Board" << std::endl;
  Graph sudoku3(9);
  sudoku3.hardHint();
  std::cout << "Number of Hints: " << sudoku.numHints() << std::endl;
  sudoku3.printBoard();
  start = std::chrono::system_clock::now();
  sudoku3.ColorBackTrack();
  end = std::chrono::system_clock::now();
  elasped_seconds = end-start;
  std::cout << "Solution" << std::endl;
  sudoku3.printBoard();
  std::cout << "Solution found in " << std::fixed << elasped_seconds.count() << " seconds\n" << std::endl;



}
