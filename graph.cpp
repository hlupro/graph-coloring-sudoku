#include "graph.h"

Graph :: Graph(int n) {
  dimension = n;
  for(int i = 1; i <=(n*n); i++) { //adds n^2 vertices to the graph
    addVertex(i);
  }

   int sqr = sqrt(n); //square root of n which is used when determining the size of the squares in a sudoku puzzle
  //For loop that finds every upper left corner of each square in a sudoku game
  for(int i = 1; i <= (n*n); i+= (n*sqr)) { //iterates through rows
     for(int j = 0; j < n; j+= sqr) { //iterates through every sqrt(n) columns
       connectSquare(i + j, sqr, n); //function to add an edge
     }
  }
  //Connects all the vertices in a single column or vertical line of a sudoku grid, since every individual square was
  //already had all its vertices added as neighbors it starts at the lowest square of i.
  int skip = 0;
  for(int i = 1; i <= n; i++){ //increments to the beginning of the next column
    skip = 0;
    for(int j = i; j <=(n*n)-(sqr *n); j+=n) { //increments down the row until the second to last square is finished
      if(j >= skip) { //if the skip variable is too old it is updated
        skip = j+(n*sqr);
      }
      for(int k = skip; k <=(n*n); k+=n) { //starts at the square below i and begins going down the rows
        addEdge(j,k);
      }
    }
  }

  // Connects all the vertices in a horizontal line, since every individual square was already counted as a neighbor it
  // finds the vertices in the other squares down the columns
  skip = 0; //int that is used to keep track of what square to skip over when adding edges
  for(int i = 1; i <= (n*n); i+=n) { //increments to the beginning of the next row
    for(int j = i; j <= i+n-1-sqr; j++) { //increments to next column until the end of the second to last square
      if(j%sqr == 1) { //if j has incremented sqr columns edit the skip variable
        skip = j+sqr;
      }
      for(int k = skip; k <= i+n-1; k++) { //finds the start of the vertices to connect at the square that starts at vertex(skip)
        addEdge(j,k);
      }
    }
  }
}

void Graph :: connectSquare(int x, int sqr, int n) {
  int* arr = new int[n]; //initialize array that will be used to connect all the edges
  int inc = -1; //array increment
  for(int i = 0; i < sqr; i++) { //for loop that populates the array with the vertices in the square
    for(int j = 0; j < sqr; j++) { //moves across the columns of the square
      inc++; //array index incremented
      arr[inc] = x+j; //vertex is stored into the temporary array. all vertices inside a sqrt(n) x sqrt(n) sqaure will be added
    }
    x = x + n; //next row is accessed
  }
  for(int i = 0; i < n-1; i++) {
    for (int j = i+1; j < n; j++) { //inner for loops makes it so the indexices before i are not access again
      addEdge(arr[i], arr[j]);
    }
  }
  delete [] arr; //deletion of temporary array
}

void Graph :: addVertex(int x) {
  if(vertices.find(x) == vertices.end()) { //Searches the map for vertex x

  std::vector<int> neighbors; //if not found initalize an empty vector
  vertices.insert({x, neighbors}); //insert x and its empty vector into the map
  color.insert({x, 0});
  }
  else {
    std::cout << "Vertex " << x << " is already in the graph."  << "\n"<< std::endl; //if already found print statement
  }
}

void Graph :: addEdge(int x, int y) {
  auto it = vertices.find(x); //iterators that are set to where x and y are in the map if found
  auto it2 = vertices.find(y);
  bool exist = false; //bool acting as a flag for inserting an edge
  if(it != vertices.end() && it2 != vertices.end()) //If statement to check if both vertices are in the graph
  {
    for(int n : it->second) { //for loop that checks adjacency list of x. if y is found then the edge already exists
      if(n == y) {            //Only need to check one list since this is an undirected graph
        std::cout << "An edge between the vertices, " << x << " and " << y << ", already exists." << "\n" << std::endl;
        exist = true; //if they exist the flag is set to true
      }
    }
    if(!exist) { //if bool is false then the edge is added by means of inserting x into y's adjacency list and vice versa.
      vertices[x].push_back(y);
      vertices[y].push_back(x);
    }
  }
  else {
    std::cout << "Error. One or both of the requested verticies are not in the graph." << "\n" << std::endl;
  }
}

void Graph :: print() { //Prints a vertex, and all of its neighbors
  for(auto it = vertices.begin(); it != vertices.end(); it++) { //For loop is set to the first vertex in the map
    std::cout << "Neighbors of vertex " << it->first <<std::endl; //it->first points to the key which is the value of the vertex
    if(it->second.empty()) //it->second points to the vector or the adjaceny list of all the neighboring vertices
    {
      std::cout << "\nThis vertex has no neighbors" << std::endl;
    }
    else {
      for(int n : it->second) { //ranged based for loop that iteratates through the vector
        std::cout << n << " ";
      }
      std::cout << "\n" << std::endl;
    }
  }
}

//Prints the graph in the shape of a Sudoku board
void Graph :: printBoard() { //Prints a vertex, and all of its neighbors
  int h = 0; //variables to keep track of position in order to print a new line or vertical line
  int v = 0;
  int z = 0; //responsible for printing new line after n vertices are printed
  int s = sqrt(dimension);
  std::cout << std::setfill('-') << std::setw(3*(dimension+s-1)) << "-" << std::endl;
  std::cout << std::setfill(' ');
  for(auto it = color.begin(); it != color.end(); it++) { //For loop is set to the first vertex in the map
    h++;
    z++;

    std::cout << std::setw(3) << std::left;
    std::cout << it->second;
    if(z == dimension) {
      v++;
      z = 0;
      std::cout << std::endl;
      h = 0;
    }
    if(h == s) {
      std::cout << std::setw(3)  << std::left;
      std::cout << "|";
      h = 0;
    }
    if(v == s) {
      std::cout << std::setfill('-') << std::setw(3*(dimension+s-1)) << "-" << std::endl;
      std::cout << std::setfill(' ');
      v = 0;
    }


  }
  std::cout << std::endl;
}

//Takes the graph and attempts to color a Sudoku solution, //Iterates through each vertex and labels the smallest value of c possibe
//if an adjacent vertex has that color n, c is incremented to the next color and the loop runs again
//Assigns vertices colors from left to right top to bottom in a sudoku board
//Doesnt work for 3x3
//Need to create one that invloves the use of backtracking
void Graph :: ColorGreedy()  {
  for(auto it = vertices.begin(); it != vertices.end(); it++) {
    int c = 1;
    int v = it->first;
    bool sameColor = true;
    if(color[v] == 0) {
      while(sameColor != false) {
        sameColor = false;
        for(int n : it->second) {
          if(color[n] == c) {
            sameColor = true;
          }
        }
        if(sameColor) {
          c++;
        }
      }
      color[it->first] = c;
    }
  }
}

void Graph :: ColorBackTrack() {
  for(int i = 0; i < unknowns.size(); i++) {
    auto it = color.find(unknowns[i]); //returns an iterator pointing to the location where color is stored
    auto v = vertices.find(unknowns[i]); //points to the current vertex's adjacency list
    int c = it->second+1; //current color of unknown at v[i];
    bool sameColor = true;
    while(sameColor != false) {
      sameColor = false;
      for(int n : v->second) {
        if(color[n] == c) {
          sameColor = true;
        }
      }
      if(sameColor) {
        c++;
      }
    }
    if(c > 9) {
      color[unknowns[i]] = 0;
      Recurse(i-1, i+1); //if no number fits go back to previous and try next option
    }
    else {
      color[unknowns[i]] = c;
    }
  }
}

// void Graph :: Recurse(int i, int stop) {
//   if(i == -1) {
//     std::cout << "Error: No Solution Found" << std::endl;
//     return;
//   }
//   if(i == unknowns.size()) {
//     return;
//   }
//   std::cout << i << std::endl;
//   // if(i == 19) {
//   //   return;
//   // }
//   auto it = color.find(unknowns[i]); //returns an iterator pointing to the location where color is stored
//   auto v = vertices.find(unknowns[i]); //points to the current vertex's adjacency list
//   int c = it->second+1; //current color of unknown at v[i];
//   bool sameColor = true;
//   while(sameColor != false) {
//     sameColor = false;
//     for(int n : v->second) {
//       if(color[n] == c) {
//         sameColor = true;
//       }
//     }
//     if(sameColor) {
//       c++;
//     }
//   }
//   if(c > 9) {
//     //std::cout << i << std::endl;
//     color[unknowns[i]] = 0;
//     Recurse(i-1); //if no number fits go back to previous and try next option
//   }
//   else {
//     color[unknowns[i]] = c;
//     Recurse(i+1);
//   }
// }

void Graph :: Recurse(int i, int stop) {
  if(i == -1) {
    std::cout << "Error: No Solution Found" << std::endl;
  }

  while(i != stop) {
    auto it = color.find(unknowns[i]); //returns an iterator pointing to the location where color is stored
    auto v = vertices.find(unknowns[i]); //points to the current vertex's adjacency list
    int c = it->second+1; //current color of unknown at v[i];
    bool sameColor = true;
    while(sameColor != false) {
      sameColor = false;
      for(int n : v->second) {
        if(color[n] == c) {
          sameColor = true;
        }
      }
      if(sameColor) {
        c++;
      }
    }
    if(c > 9) {
      //std::cout << i << std::endl;
      color[unknowns[i]] = 0;
      i--; //if no number fits go back to previous and try next option
    }
    else {
      color[unknowns[i]] = c;
      i++;
    }
  }
}

void Graph :: easyHint() {
  std::ifstream inFile;
  inFile.open("hint.txt");
  for(int i = 1; i <= 81; i++) {
    inFile >> color[i];
  }
  inFile.close();
  addUnknowns();
}

void Graph :: intermediateHint() {
  std::ifstream inFile;
  inFile.open("hint2.txt");
  for(int i = 1; i <= 81; i++) {
    inFile >> color[i];
  }
  inFile.close();
  addUnknowns();
}

void Graph :: hardHint() {
  std::ifstream inFile;
  inFile.open("hint3.txt");
  for(int i = 1; i <= 81; i++) {
    inFile >> color[i];
  }
  inFile.close();
  addUnknowns();
}

int Graph :: numHints() {
  return unknowns.size();
}

void Graph :: addUnknowns() {
  for(auto it = color.begin(); it != color.end(); it++) {
    if(it->second == 0) {
      unknowns.push_back(it->first);
    }
  }
}
