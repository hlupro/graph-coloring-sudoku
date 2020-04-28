#include "graph.h"

Graph :: Graph(int n) {
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
  color.insert({x, white});
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

void Graph :: printBfs(int x) { //performs a BFs starting on vertex x if it exists
  std::cout << "//Beginning a BFS starting at vertex " << x  << "//"<< std::endl;
  if(vertices.find(x) != vertices.end()) { //Checks if x is a vertex in the graph

    enum color_t {white, grey, black}; //enum declared to keep track of colors

    std::map<int, color_t> color; //map for color
    std::map<int, int> parent; //map for parent
    std::map<int, int> distance; //map for distance
    std::queue<int> q; //Will keep track of visted vertices

    for(auto it = vertices.begin(); it != vertices.end(); it++) { //initalizing all vertex colors to be white,
      color.insert({it->first, white});
    }

    color[x] = grey; //starting node is marked as visited
    distance.insert({x, 0});
    q.push(x); //inserted into queue

    while(!q.empty()) {
      bool neighbors = false; //bool used for print statement
      int u = q.front();
      q.pop();
      std::cout << "Vertex: " << u << std::endl;
      if(parent.find(u) != parent.end()) { //if not found in parent map it must be the starting node
        std::cout << "Parent: " << parent[u] << std::endl;
      }
      else {
        std::cout << u << " is the starting vertex." << std::endl;
      }
      std::cout << "Distance: " << distance[u] << std::endl;
      std::cout << "Unvisited Neighboring Vertices: ";
      auto it = vertices.find(u); //iterator set to u's position in map
      for(int n : it->second) { //iteratates through u's neighbors and marking them grey
        if(color[n] == white) { //if any white vertices are found find their distance, color them grey and mark their parent as u
          neighbors = true;
          color[n] = grey;
          distance.insert({n, distance[u] +1});
          parent.insert({n, u});
          q.push(n); //insert into queue
          std::cout << n << " ";
        }

        color[u] = black; //u is now fully explored
      }
      if(!neighbors) {
        std::cout << "None.";
      }
      std::cout << "\n" << std::endl;
    }
  }
  else //if x is not in the graph print out an error message
  {
    std::cout << "Error. Cannot do a BFS because " << x << " is not a vertex in the graph." << "\n" << std::endl;
  }
}
