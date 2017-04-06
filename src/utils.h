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

const double PI  =3.141592653589793238463;

vector<float> heights;
vector<pair<int, int> > sharingPoints;

void printMap(Graph<Local> &map, int id, vector<int> path){

	//TODO ruas com nomes e mais decentes; depois dos edges grafo está pronto

	int idEdge = 0;
	GraphViewer gv(1800, 1200, false);
	gv.setBackground("background.jpg");
	gv.createWindow(1800, 1200);

	float lonDiff = MAX_LON - MIN_LON;
	float latDiff = MAX_LAT - MIN_LAT;

	gv.defineEdgeDashed(true);
	gv.defineVertexColor("blue");
	gv.defineEdgeColor("black");


	vector<Vertex<Local>* > vertexes = map.getVertexSet();
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

		if(vertexes.at(i)->getInfo().getUXid() == id){
			gv.setVertexSize(vertexes.at(i)->getInfo().getUXid(), 80);
			gv.setVertexIcon(vertexes.at(i)->getInfo().getUXid(), "here.png");
		}

		vector<int>::iterator it = find(path.begin(), path.end(), vertexes.at(i)->getInfo().getUXid());
		if(it != path.end()){
			gv.setVertexSize(vertexes.at(i)->getInfo().getUXid(), 40);
			gv.setVertexIcon(vertexes.at(i)->getInfo().getUXid(), "path.png");
		}
	}

	for(size_t i = 0; i < vertexes.size(); i++){
		vector<Edge<Local> > edges = vertexes.at(i)->getAdj();
		for(size_t j = 0; j < edges.size(); j++){
			gv.addEdge(idEdge, vertexes.at(i)->getInfo().getUXid(), edges.at(j).getDest()->getInfo().getUXid(), EdgeType::DIRECTED);

			string road;
			for(size_t k = 0; k < vertexes.at(i)->getInfo().getRoads().size(); k++){
				for(size_t l = 0; l < edges.at(j).getDest()->getInfo().getRoads().size(); l++){
					if(vertexes.at(i)->getInfo().getRoads().at(k) == edges.at(j).getDest()->getInfo().getRoads().at(l)){
						road = vertexes.at(i)->getInfo().getRoads().at(k).	//TODO retirar nome da rua;
					}
				}
			}

			gv.setEdgeLabel(idEdge, road);
			gv.setEdgeColor(idEdge, "yellow");
			idEdge++;
		}
	}


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
