#include <iostream>

#include "Graph.h"
#include "MenusManager.h"
#include "Parsers.h"
#include <vector>
#include "Local.h"
#include "graphviewer.h"
#include "utils.h"
using namespace std;

//TODO depois começar a ver as opçoes que tenho de ter no menu e como usar a informaçao guardada no grafo

int main(){

	//TODO isto vai ser chamado só quando o user escolher o criterio para se construir o grafo com os pesos de acorda com a suas prioridades
	Graph<Local> map;
	readLocals(map);
	readStreets(map, SHORTEST_DIST);
	readRoadsDirections(map);
	vector<int> sharingPoints = setRegionSharingPoints(map);	//TODO isto e o vetor debaixo vai ser atribuido apenas quando o programa for iniciado e depois é usado sempre o mesmo vetor de sharing points (var global??) para todas as iteraçoes do grafo
	vector<int> heights = setHeights(map);

	//TODO isto vai ser primeiro
	cout << "Welcome to this BikeSharing Platform!";
	displayMainMenu(map);


	// teste de graph

	pair<float, float> coord1(0, 0);
	Local Local1(1, coord1, 0);
	pair<float, float> coord2(0, 5);
	Local Local2(2, coord2, 0);
	pair<float, float> coord3(0, -3);
	Local Local3(3, coord3, 0);
	pair<float, float> coord4(0, 4);
	Local Local4(4, coord4, 0);
	//Local4.setSharingPoint();		TODO dar lhe um sharing point se quiser testr isto direito

	Graph<Local> graph;

	graph.addVertex(Local1);
	graph.addVertex(Local2);
	graph.addVertex(Local3);
	graph.addVertex(Local4);

	graph.addEdge(Local1, Local2, Local1.getWeight(Local2, SHORTEST_DIST));
	graph.addEdge(Local1, Local3, Local1.getWeight(Local3, SHORTEST_DIST));
	graph.addEdge(Local2, Local4, Local2.getWeight(Local4, SHORTEST_DIST));
	graph.addEdge(Local2, Local3, Local2.getWeight(Local3, SHORTEST_DIST));
	graph.addEdge(Local3, Local2, Local3.getWeight(Local2, SHORTEST_DIST));
	cout << "d1,2,4=" << Local1.getWeight(Local2, SHORTEST_DIST) + Local2.getWeight(Local4, SHORTEST_DIST) << endl;
	cout << "d1,3,4=" << Local1.getWeight(Local3, SHORTEST_DIST) + Local3.getWeight(Local4, SHORTEST_DIST) << endl;
	vector<Local> v = graph.dfs();
	for (unsigned int i = 0; i < v.size(); i++){
		v.at(i).print();
	}

	//teste da search

	graph.dijkstraShortestPath(Local1);		////TODO fazer funçao para encontrar menor caminho usando o dijktras e acrescentando verificaçao se tem lugares disponiveis
	int min = 123871;
	int id = -1;
	size_t j;
	for(j = 0; j < graph.getVertexSet().size(); j++){
		if(graph.getVertexSet().at(j)->getInfo().getSharingPoint().first && graph.getVertexSet().at(j)->getInfo().getSharingPoint().second > 0 && graph.getVertexSet().at(j)->getDist() < min){
			min=graph.getVertexSet().at(j)->getDist();
			id=graph.getVertexSet().at(j)->getInfo().getId();
			break;
		}
	}

	//for(size_t i=0; i < graph.getPath(graph.getVertexSet().at(j)).size(); i++) {	//TODO fazer funçao para imprimir caminho
		//cout << graph.getPath(graph.getVertexSet().at(j)).at(i).getId() << " - ";
	//}




	return 0;
}
