#include <iostream>

#include "Graph.h"
#include "Node.h"
#include "MenusManager.h"
#include <vector>
using namespace std;


//TODO tentar descobrir como sao os ficheiros do open street map para ir la criar localizaçoes e fazer parder para os ficheiros txt com a info dessas localizaçoes e por no grafo
//TODO depois começar a ver as opçoes que tenho de ter no menu e como usar a informaçao guardada no grafo


int main(){
	cout << "Welcome to this BikeSharing Platform!";
	displayMainMenu();

	pair<float, float> coord1(1, 2);
	Node node1("no1", coord1, 1.5);
	pair<float, float> coord2(2, 2);
	Node node2("no2", coord2, 1.5);
	pair<float, float> coord3(3, 6);
	Node node3("no3", coord3, 3);
	Graph<Node> graph;

	graph.addVertex(node1);
	graph.addVertex(node2);
	graph.addVertex(node3);
	cout << endl << graph.getNumVertex() << endl;

	graph.addEdge(node1, node3, node1.getDistance(node3));
	graph.addEdge(node3, node2, node3.getDistance(node2));
	vector<Node> v = graph.dfs();
	for (unsigned int i = 0; i < v.size(); i++){
		v.at(i).print();
	}
	graph.removeVertex(node1);
	cout << endl << graph.getNumVertex();

	return 0;
}
