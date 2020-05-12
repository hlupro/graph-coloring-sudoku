#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <chrono>


class Graph{
private:
  /* will map an int to a list of its neighbors */
  std::map<int, std::vector<int>> vertices; //adjacency list using vector class
  std::map<int, int> color; //map that maps two ints, the first int is the vertex and the second is the color
  std::vector<int> unknowns; //A vector of all vertices whose coloring is zero
  int dimension; //int that is the dimension of the puzzle ie a 9x9

public:
  Graph(int n);
  void addVertex(int x); // add a vertex to the graph
  void addEdge(int x, int y); // add an undirected edge to the graph
  void print(); // prints the adjacency list of each vertex, to show the structure
  void printBoard(); //Prints the color of each vertex in a Sudoku board format
  void connectSquare(int x, int sqr, int n); //
  void ColorGreedy(); //A simple greedy algorithm that colors the graph
  void ColorBackTrack();
  void easyHint(); //precolors the graph to match an easy sudoku puzzle
  void intermediateHint(); //precolors the graph to match an intermediate sudoku puzzle
  void hardHint(); //precolors the graph to match a hard sudoku puzzle
  void addUnknowns(); //Populates the vector unknowns with all the vertices who's color is 0.
  void backtrack(int i, int stop);
  int numHints(); //returns the number of hints a sudoku puzzle begins with
};

#endif
