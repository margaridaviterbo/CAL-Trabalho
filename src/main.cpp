#include <iostream>

#include "Graph.h"
#include "Node.h"
#include "MenusManager.h"
using namespace std;


int main(){
	cout << "Welcome to this BikeSharing Platform!";
	displayMainMenu();

	pair<float, float> coord1(1, 2);
	Node node1("no1", coord1, 1.5);
	Graph<Node> graph;
	graph.addVertex(node1);

	cout << endl << graph.getNumVertex();

	return 0;
}
