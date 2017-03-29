#include <iostream>

#include "Graph.h"
#include "MenusManager.h"
#include "Parsers.h"
#include <vector>
#include "Local.h"
//#include "Road.h"
using namespace std;


//TODO depois começar a ver as opçoes que tenho de ter no menu e como usar a informaçao guardada no grafo


int main(){

	Graph<Local> map;

	readLocals(map);
	readStreets(map);
	readRoadsDirections(map);

	vector<Local> v1 = map.dfs();
		for (unsigned int i = 0; i < v1.size(); i++){
			v1.at(i).print();
		}

	cout << "Welcome to this BikeSharing Platform!";
	displayMainMenu();


	// teste de graph

	pair<float, float> coord1(1, 2);
	Local Local1(1, coord1, 1);
	pair<float, float> coord2(2, 2);
	Local Local2(2, coord2, 1);
	pair<float, float> coord3(3, 6);
	Local Local3(3, coord3, 3);
	Graph<Local> graph;

	graph.addVertex(Local1);
	graph.addVertex(Local2);
	graph.addVertex(Local3);
	cout << endl << graph.getNumVertex() << endl;

	graph.addEdge(Local1, Local3, Local1.getDistance(Local3));
	graph.addEdge(Local3, Local2, Local3.getDistance(Local2));
	vector<Local> v = graph.dfs();
	for (unsigned int i = 0; i < v.size(); i++){
		v.at(i).print();
	}
	graph.removeVertex(Local1);
	cout << endl << graph.getNumVertex();

	//fim do teste do parser


	return 0;
}
