#include <iostream>

#include "Graph.h"
#include "MenusManager.h"
#include "Parsers.h"
#include <vector>
#include "Local.h"
//#include "Road.h"
using namespace std;


//TODO depois come�ar a ver as op�oes que tenho de ter no menu e como usar a informa�ao guardada no grafo


int main(){

	Graph<Local> map;

	readLocals(map);
	readStreets(map);
	readRoadsDirections(map);


	cout << "Welcome to this BikeSharing Platform!";
	displayMainMenu();


	// teste de graph

	pair<float, float> coord1(0, 0);
	Local Local1(1, coord1, 0);
	pair<float, float> coord2(0, 5);
	Local Local2(2, coord2, 0);
	pair<float, float> coord3(0, -3);
	Local Local3(3, coord3, 0);
	pair<float, float> coord4(0, 4);
	Local Local4(4, coord4, 0);
	Local4.isDeliveryPoint=true;
	//pair<float, float> coord5(0, 6);
	//Local Local5(5, coord5, 0);
	Graph<Local> graph;

	graph.addVertex(Local1);
	graph.addVertex(Local2);
	graph.addVertex(Local3);
	graph.addVertex(Local4);
	//graph.addVertex(Local5);

	graph.addEdge(Local1, Local2, Local1.getDistance(Local2));
	graph.addEdge(Local1, Local3, Local1.getDistance(Local3));
	graph.addEdge(Local2, Local4, Local2.getDistance(Local4));
	graph.addEdge(Local2, Local3, Local2.getDistance(Local3));
	graph.addEdge(Local3, Local2, Local3.getDistance(Local2));
	cout << "d1,2,4=" << Local1.getDistance(Local2) + Local2.getDistance(Local4) << endl;
	cout << "d1,3,4=" << Local1.getDistance(Local3) + Local3.getDistance(Local4) << endl;
	vector<Local> v = graph.dfs();
	for (unsigned int i = 0; i < v.size(); i++){
		v.at(i).print();
	}


	graph.dijkstraShortestPath(Local1);		////TODO fazer fun�ao para encontrar menor usando o dijktras
	int min = 123871;
	int id = -1;
	size_t j;
	for(j = 0; j < graph.getVertexSet().size(); j++){
		if(graph.getVertexSet().at(j)->getInfo().isDeliveryPoint == true && graph.getVertexSet().at(j)->getDist() < min){
			min=graph.getVertexSet().at(j)->getDist();
			id=graph.getVertexSet().at(j)->getInfo().getId();
			break;
		}
	}

	cout << id << endl << min;


	for(size_t i=0; i < graph.getPath(graph.getVertexSet().at(j)).size(); i++) {	//TODO fazer fun�ao para imprimir caminho
		cout << graph.getPath(graph.getVertexSet().at(j)).at(i).getId() << " - ";
	}





	//fim do teste do parser


	return 0;
}
