#ifndef UTILS_H
#define UTILS_H


#include <iostream>
#include "Graph.h"
#include "Local.h"
#include "Parsers.h"
#include "graphviewer.h"
#include "math.h"
#include "string"
#include "algorithm"

using namespace std;

#define MIN_LAT 41.20
#define MAX_LAT 41.25
#define MIN_LON -8.59
#define MAX_LON -8.63
#define WIN_WIDTH 3000
#define WIN_HEIGHT 3000

const double PI = 3.141592653589793238463;

vector<float> heights;
vector<pair<int, int> > sharingPoints;

/**
 * função que implementa o graphViewer para desenhar o grafo
 * @param mapa é o grafo a representar
 * @param id é o id do local onde se encontra o user
 * @param path é o vetor de ids do caminho encontrado
 */
void printMap(Graph<Local> &mapa, int id, vector<int> path){

	int idEdge = 0;
	GraphViewer gv(1800, 1200, false);
	gv.setBackground("background.png");
	gv.createWindow(1800, 1200);

	float lonDiff = MAX_LON - MIN_LON;
	float latDiff = MAX_LAT - MIN_LAT;

	gv.defineEdgeDashed(false);
	gv.defineVertexColor("blue");
	gv.defineEdgeColor("yellow");


	vector<Vertex<Local>* > vertexes = mapa.getVertexSet();
	for(size_t i = 0; i < vertexes.size(); i++){
		int x = (int)((MAX_LON - vertexes.at(i)->getInfo().getCoordinates().second)/(lonDiff) * WIN_WIDTH)*6;
		int y = (int)((MAX_LAT - vertexes.at(i)->getInfo().getCoordinates().first)/(latDiff) * WIN_HEIGHT)*6;
		gv.addNode(vertexes.at(i)->getInfo().getUXid(), x - 1000*6, y - 1100*6);

		if(vertexes.at(i)->getInfo().getSharingPoint().first){
			stringstream sstm;
			sstm << "Available spots: " << vertexes.at(i)->getInfo().getSharingPoint().second;
			string label = sstm.str();
			gv.setVertexLabel(vertexes.at(i)->getInfo().getUXid(), label);
			gv.setVertexSize(vertexes.at(i)->getInfo().getUXid(), 40);
			gv.setVertexIcon(vertexes.at(i)->getInfo().getUXid(), "bike.png");
		}

		if(vertexes.at(i)->getInfo().getCityCenter()){
			gv.setVertexSize(vertexes.at(i)->getInfo().getUXid(), 80);
			gv.setVertexIcon(vertexes.at(i)->getInfo().getUXid(), "center.png");
		}

		if(vertexes.at(i)->getInfo().getUXid() == id){
			gv.setVertexSize(vertexes.at(i)->getInfo().getUXid(), 80);
			gv.setVertexIcon(vertexes.at(i)->getInfo().getUXid(), "here.png");
		}

		vector<int>::iterator it = find(path.begin(), path.end(), vertexes.at(i)->getInfo().getUXid());
		if(it != path.end() && !vertexes.at(i)->getInfo().getSharingPoint().first) {
			gv.setVertexSize(vertexes.at(i)->getInfo().getUXid(), 40);
			gv.setVertexIcon(vertexes.at(i)->getInfo().getUXid(), "path.png");
		}
	}

	for(size_t i = 0; i < vertexes.size(); i++){
		vector<Edge<Local> > edges = vertexes.at(i)->getAdj();
		for(size_t j = 0; j < edges.size(); j++){
			gv.addEdge(idEdge, vertexes.at(i)->getInfo().getUXid(), edges.at(j).getDest()->getInfo().getUXid(), EdgeType::DIRECTED);

			map<unsigned long long, string> roads1 = vertexes.at(i)->getInfo().getRoads();
			map<unsigned long long, string> roads2 = edges.at(j).getDest()->getInfo().getRoads();
			map<unsigned long long, string>::const_iterator it1 = roads1.begin();
			map<unsigned long long, string>::const_iterator it1_e = roads1.end();
			map<unsigned long long, string>::const_iterator it2 = roads2.begin();
			map<unsigned long long, string>::const_iterator it2_e = roads2.end();

			while((it1 != it1_e) && (it1->first != it2->first)){

				cout << "while 1\n";
				cout << "it1-first " << it1->first << "it2-first " << it2->first << endl;

				it2 = roads2.begin();
				it2_e = roads2.end();

				while((it1 != it1_e) && (it2 != it2_e) && (it1->first != it2->first)){
					cout << "while 2\n";
					cout << "it1-first " << it1->first << "it2-first " << it2->first << endl;
					it2++;
				}
				if(it1->first == it2->first){
					break;
				}
				it1++;
			}
			string road = it2->second;
			gv.setEdgeLabel(idEdge, road);

			vector<int>::iterator node1 = find(path.begin(), path.end(), vertexes.at(i)->getInfo().getUXid());
			vector<int>::iterator node2 = find(path.begin(), path.end(), edges.at(j).getDest()->getInfo().getUXid());
			if((node1 != path.end() || vertexes.at(i)->getInfo().getUXid() == id) && (node2 != path.end() || edges.at(j).getDest()->getInfo().getUXid() == id)){
				gv.setEdgeColor(idEdge, "green");
			}


			gv.setEdgeThickness(idEdge, 10);
			idEdge++;
		}
	}
}

/**
 * funçao que elabora um vetor com informaçoes sobre os pontos de partilha
 * @param map é o grafo que representa o mapa
 */
vector<pair<int, int> > setRegionSharingPoints(Graph<Local> &map){

	int numLocals = map.getNumVertex();
	size_t numSharingPoints = (int)(0.5*numLocals);
	vector<pair<int, int> > sp;
	int pos;
	int freeSpots;
	bool b = false;

	for(int i = 0; i < numLocals; i++){
		freeSpots = rand() % 15;
		sp.push_back(pair<int, int>(0, freeSpots));
	}

	for(; numSharingPoints > 0; numSharingPoints--){
		do{
			pos = rand() % numLocals;
			b = false;
			if(sp.at(pos).first == 0)
				sp.at(pos).first = 1;
			else
				b = true;
		}while(b == true);
	}

	return sp;
}

void adjustSharingPoints(Graph<Local> &map){
	for(size_t i = 0; i < map.getVertexSet().size(); i++){

		if(map.getLocal((int)i)->getSharingPoint().first){
			if(map.getLocal((int)i)->getRoads().size() < 2){
				map.getLocal((int)i)->setSharingPoint(pair<bool, int>(false, 0));
			}
		}
	}
}

/**
 * funçao que cria um vetor com valores de alturas para locais
 * @param map é o grafo que representa o mapa
 */
vector<float> setHeights(Graph<Local> &map){

	int numLocals = map.getNumVertex();
	vector<float> heights;
	float h;

	for(int i = 0; i < numLocals; i++){
		h = (float)(rand() % 11) / 1000.0;
		heights.push_back(h);
	}
	return heights;
}

/**
 * funçao que define o centro geografico da cidade
 * @param map é o grafo que representa a cidade
 */
void setCityCenter(Graph<Local> &map){

	vector<double> latitudes;
	vector<double> longitudes;
	vector<double> diffLatitudes;
	vector<double> diffLongitudes;
	vector<double> diffTotal;
	double sumLat = 0;
	double sumLon = 0;

	for(size_t i = 0; i < map.getVertexSet().size(); i++){
		latitudes.push_back(map.getVertexSet().at(i)->getInfo().getCoordinates().first);
		longitudes.push_back(map.getVertexSet().at(i)->getInfo().getCoordinates().second);
		sumLat = sumLat + map.getVertexSet().at(i)->getInfo().getCoordinates().first;
		sumLon = sumLon + map.getVertexSet().at(i)->getInfo().getCoordinates().second;
	}

	double medLat = sumLat/latitudes.size();
	double medLon = sumLon/longitudes.size();

	for(size_t i = 0; i < map.getVertexSet().size(); i++){
		diffLatitudes.push_back(abs(map.getVertexSet().at(i)->getInfo().getCoordinates().first - medLat));
		diffLongitudes.push_back(abs(map.getVertexSet().at(i)->getInfo().getCoordinates().second - medLon));
		diffTotal.push_back(diffLatitudes.at(i) + diffLongitudes.at(i));
	}

	vector<double>::iterator it = min_element(diffTotal.begin(), diffTotal.end());
	size_t i;
	for(i = 0; i < diffTotal.size(); i++){
		if(diffTotal.at(i) == *(it)){
			break;
		}
	}

	Local *lC = map.getLocal((int)i);
	lC->setCityCenter();

	for(size_t i = 0; i < map.getVertexSet().size(); i++){
		map.getLocal((int)i)->setDiffDistCenter(map.getVertexSet().at(i)->getInfo().getWeight(*lC, SHORTEST_DIST));
		map.getLocal((int)i)->setDiffHeightCenter(map.getVertexSet().at(i)->getInfo().getWeight(*lC, SHORTEST_HEIGHT));
	}



}

/**
 * funçao que constroi o grafo
 * @param op é a opçao de pesquisa escolhida pelo user
 * @param city é a cidade sobre a qual se vai construir o grafo
 */
void builtGraph(Graph<Local> &map, searchOptions op, int city){

	string file1, file2, file3;

	switch (city){
	case 1:
		file1 = "files/A.txt";
		file2 = "files/C.txt";
		file3 = "files/B.txt";
		break;
	case 2:
		file1 = "files/A1.txt";
		file2 = "files/C1.txt";
		file3 = "files/B1.txt";
		break;
	case 3:
		file1 = "files/A2.txt";
		file2 = "files/C2.txt";
		file3 = "files/B2.txt";
		break;
	}

	Graph<Local> temp;
	if(heights.size() == 0){
		readLocals(temp, heights, sharingPoints, file1);
		heights = setHeights(temp);
		sharingPoints = setRegionSharingPoints(temp);
	}

	readLocals(map, heights, sharingPoints, file1);
	readStreets(map, op, file2);
	readRoadsDirections(map, op, file3);
	adjustSharingPoints(map);
	setCityCenter(map);

}



#endif UTILS_H	/* UTILS_H */
