#ifndef UTILS_H
#define UTILS_H


#include <iostream>
#include "Graph.h"
#include "Local.h"
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

void printMap(Graph<Local> &map){

	//TODO melhorar coordenadas x,y
	//TODO definir com formas, icons, texto, cores diferentes nós especiais

	int idEdge = 0;
	GraphViewer gv(600, 600, false);
	gv.setBackground("background.jpg"); //TODO por no background print do bocado do mapa original correspondente às infos do ficheiro
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

	Sleep(20000);
}

vector<int> setRegionSharingPoints(Graph<Local> &map){

	int numLocals = map.getNumVertex();
	size_t numSharingPoints = (int)(0.1*numLocals);
	vector<int> sp;
	int pos;
	bool b = false;

	for(int i = 0; i < numLocals; i++){
		sp.push_back(0);
	}

	for(; numSharingPoints > 0; numSharingPoints--){
		do{
			pos = rand() % numLocals;
			b = false;
			if(sp.at(pos) == 0)
				sp.at(pos) = 1;
			else
				b = true;
		}while(b == true);
	}

	return sp;
}

vector<int> setHeights(Graph<Local> &map){

	int numLocals = map.getNumVertex();
	vector<int> heights;
	int h;

	for(int i = 0; i < numLocals; i++){
		h = (rand() % 11) / 100;
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

	for(size_t i; i < map.getVertexSet().size(); i++){
		latitudes.push_back(map.getVertexSet().at(i)->getInfo().getCoordinates().first);
		longitudes.push_back(map.getVertexSet().at(i)->getInfo().getCoordinates().second);
		sumLat = sumLat + map.getVertexSet().at(i)->getInfo().getCoordinates().first;
		sumLon = sumLon + map.getVertexSet().at(i)->getInfo().getCoordinates().second;
	}

	double medLat = sumLat/latitudes.size();
	double medLon = sumLon/longitudes.size();

	for(size_t i; i < map.getVertexSet().size(); i++){
		diffLatitudes.push_back(abs(map.getVertexSet().at(i)->getInfo().getCoordinates().first - medLat));
		diffLongitudes.push_back(abs(map.getVertexSet().at(i)->getInfo().getCoordinates().second - medLon));
		diffTotal.push_back(diffLatitudes.at(i) + diffLongitudes.at(i));
	}

	vector<double>::iterator it = min_element(diffTotal.begin(), diffTotal.end());
	size_t i;
	for(i = 0; i < diffTotal.size(); i++){
		if(diffTotal.at(i) == *(it))
			break;
	}

	Local lC = map.getVertexSet().at(i)->getInfo();
	map.getVertexSet().at(i)->getInfo().setCityCenter();

	for(size_t i = 0; i < map.getVertexSet().size(); i++){
		map.getVertexSet().at(i)->getInfo().setDiffDistCenter(map.getVertexSet().at(i)->getInfo().getWeight(lC, SHORTEST_DIST));
		map.getVertexSet().at(i)->getInfo().setDiffHeightCenter(map.getVertexSet().at(i)->getInfo().getWeight(lC, SHORTEST_HEIGHT));
	}



}

#endif UTILS_H	/* UTILS_H */
