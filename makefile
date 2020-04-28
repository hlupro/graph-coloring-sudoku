proj: projectDriver.o graph.o
	g++ -std=c++11 -o proj projectDriver.o graph.o

graph.o: graph.cpp
	g++ -std=c++11 -c -g graph.cpp

projectDriver.o: projectDriver.cpp
	g++ -std=c++11 -c -g projectDriver.cpp

clean:
	rm *.o proj
