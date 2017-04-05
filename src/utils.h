#ifndef UTILS_H
#define UTILS_H


#include <iostream>
#include "Graph.h"
#include "Local.h"
#include "Parsers.h"
#include "graphviewer.h"
#include "math.h"

using namespace std;

#define MIN_LAT 41.20
#define MAX_LAT 41.25
#define MIN_LON -8.59
#define MAX_LON -8.63
#define WIN_WIDTH 3000
#define WIN_HEIGHT 3000

const double PI  =3.141592653589793238463;

vector<float> heights;
vector<pair<int, int> > sharingPoints;

void printMap(Graph<Local> &map){

	//TODO melhorar coordenadas x,y (so multiplicar lat e lon para aparecer logo mais afastado)
	//TODO definir com formas, icons, texto, cores diferentes n�s especiais
	//TODO mudar id's dos nodes para um sequencial (tenho de criar outro id sequencial nos nodes)

	int idEdge = 0;
	GraphViewer gv(600, 600, false);
	gv.setBackground("background.jpg"); //TODO por no background print do bocado do mapa original correspondente �s infos do ficheiro
	gv.createWindow(600, 600);

	float lonDiff = MAX_LON - MIN_LON;
	float latDiff = MAX_LAT - MIN_LAT;

	gv.defineEdgeDashed(true);
	gv.defineVertexColor("blue");
	gv.defineEdgeColor("black");


	vector<Vertex<Local>* > vertexes = map.getVertexSet();
	for(size_t i = 0; i < vertexes.size(); i++){
		int x = (int)((MAX_LON - vertexes.at(i)->getInfo().getCoordinates().second)/(lonDiff) * WIN_WIDTH);
		int y = (int)((MAX_LAT - vertexes.at(i)->getInfo().getCoordinates().first)/(latDiff) * WIN_HEIGHT);
		gv.addNode(vertexes.at(i)->getInfo().getId(), x - 600, y - 600);
	}

	for(size_t i = 0; i < vertexes.size(); i++){
		vector<Edge<Local> > edges = vertexes.at(i)->getAdj();
		for(size_t j = 0; j < edges.size(); j++){
			gv.addEdge(idEdge, vertexes.at(i)->getInfo().getId(), edges.at(j).getDest()->getInfo().getId(), EdgeType::DIRECTED);
			idEdge++;
		}
	}





	/*gv.setVertexLabel(1, "Isto e O PRIMEIRO NO");
	gv.setEdgeLabel(1, "Isto e a segunda aresta");

	gv.setVertexColor(2, "green");
	gv.setEdgeColor(1, "yellow");

	gv.setVertexSize(2, 40);
	gv.setVertexIcon(0, "icon.gif");

	gv.setEdgeDashed(1, false);*/

	//Sleep(20000);
}

vector<pair<int, int> > setRegionSharingPoints(Graph<Local> &map){

	int numLocals = map.getNumVertex();
	size_t numSharingPoints = (int)(0.1*numLocals);
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

void builtGraph(Graph<Local> &map, searchOptions op){

	Graph<Local> temp;
	if(heights.size() == 0){
		readLocals(temp, heights, sharingPoints);
		heights = setHeights(temp);
		sharingPoints = setRegionSharingPoints(temp);
	}

	readLocals(map, heights, sharingPoints);
	readStreets(map, op);
	readRoadsDirections(map, op);
	setCityCenter(map);

}



#endif UTILS_H	/* UTILS_H */
