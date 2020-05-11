#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <vector>


class Graph{
private:
  /* will map an int to a list of its neighbors */
  std::map<int, std::vector<int>> vertices; //adjacency list using vector class
  std::map<int, int> color;
  std::vector<int> unknowns;
  int dimension;

public:
  Graph(int n);
  void addVertex(int x); // add a vertex to the graph
  void addEdge(int x, int y); // add an undirected edge to the graph
  void print(); // prints the adjacency list of each vertex, to show the structure
  void printBoard(); //Prints the color of each vertex in a Sudoku board format
  void connectSquare(int x, int sqr, int n); //
  void ColorGreedy(); //A simple greedy algorithm that colors the graph
  void ColorBackTrack();
  void easyHint();
  void hardHint();
  void addUnknowns();
  void Recurse(int i);
};

#endif
