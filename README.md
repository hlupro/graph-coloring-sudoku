# graph-coloring-sudoku
Project that focuses on the relationship between Sudoku and graph coloring algortihms

#Aim
The goal of this project is to convert a 9x9 Sudoku board to a graph object in order to
run graph coloring algorithms to find solutions to a Sudoku puzzle.

#How-to-run
All the files needed are inside the zip just type make and then ./proj

#Documentation
The class works to create a Sudoku graph by using two map structures, one map that maps each vertices, 1-81 to ins
own adjacency list and the other which maps an int to another int which serves at the coloring of that vertex. The
vector unknowns is a collection of all uncolored vertices found by the function addUnknowns().
The Vertices and Edges of a sudoku graph are all calculated and predetermined inside the constructure by making use of nest for loops so that no edge is added twice and no unnecessary work is done.

Once a Sudoku graph is initialized it is then precolored through the use the hint functions which read in integers from a txt file to fill in a specific color for a specific vertex. The addUnknown function then iterates through the color map and inserts all uncolored vertices into the vector unknowns.

There are two algorithms that were used in testing to find a solution to sudoku puzzles. The first is ColorGreedy() and was a very simplistic approach that consisted of a while loop that incremented a varible c until no vertex the adjacency list had that same color, and once that was found the vertex v was colored as c. This did not work well and did not result in any correct solutions to any of the sudoku puzzles tested. This was due to the inability of the algorithm to backtrack and go back to previous vertices in order to try a new coloring.

The next algorithm ColorBackTrack() implements this idea and works by iterating on the vector unknowns, starting at the beginning and going up to the end. During each iteration the color algorithm works as the previous with a while loop incremented an integer c until c is a not used by any other vertices in the adjacency list. The difference lies in when a proper coloring of c cannot be found, the algorithm calls backtrack(i-1,i+1). Backtrack works by beginning on the vertex in the vector just before i(i-1) and trying the next possible coloring. If that coloring works then i is incremented and the first vertex tries to be colored again but if a proper coloring can't be found i is decremented until a vertex in the vector can be properly colored. This process goes back and forth until the a proper coloring is found.

Using the ColorBackTrack() algorithm solutions to each sudoku puzzle presented was able to be found and printed out. Even on the hard difficulty of puzzles.

#Future
Plans for the future include a way for the user to enter their own personal Sudoku puzzles
Compare different graph coloring algorithms to see which one is more efficient, maybe one that determines preemptive sets based on Crook's algorithm for doing Sudoku by hand.
Potentially create a Sudoku game that has the user guess the coloring of each cell and the program will determine if thats wrong
or not.  
