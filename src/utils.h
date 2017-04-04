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
	//seleciona o no centro e TODO atribui a todos as nos a sua distancia e altura em relaçao ao centro
	Local* cityCenter1 = new Local();
	Local* cityCenter2 = new Local();
	vector<double> latitudes;
	vector<double> longitudes;

	for(size_t i; i < map.getVertexSet().size(); i++){
		latitudes.push_back(map.getVertexSet().at(i)->getInfo().getCoordinates().first);
		longitudes.push_back(map.getVertexSet().at(i)->getInfo().getCoordinates().second);
	}

	sort(latitudes.begin(), latitudes.end());
	sort(longitudes.begin(), longitudes.end());

	int med = (int)latitudes.size()/2;

	int i = 0;
	int k = med;
	bool found = false;
	do{
		if(map.getLocal(latitudes.at(k))->getCoordinates().second == longitudes.at(k)
				|| map.getLocal(latitudes.at(k))->getCoordinates().second == longitudes.at(k-1)
				|| map.getLocal(latitudes.at(k))->getCoordinates().second == longitudes.at(k+1)){
			cityCenter1 = map.getLocal(latitudes.at(k));
			found = true;
		}
		else if(map.getLocal(latitudes.at(k-1))->getCoordinates().second == longitudes.at(k)){
			cityCenter1 = map.getLocal(latitudes.at(k-1));
			found = true;
		}
		else if(map.getLocal(latitudes.at(k+1))->getCoordinates().second == longitudes.at(k)){
			cityCenter1 = map.getLocal(latitudes.at(k+1));
			found = true;

		}
		k++;
	}while(found == false && k < latitudes.size() - 1);


	int j = 0;
	k = med-1;
	found = false;
	do{
//copiar o de cima
		k--;
	}while(found == false && k > 0);

	//casos se chegar aos extremos

	//ver qual qhile tem menos iteraçoes
	//selecionar qual dos citycenters
	//alterar propriedade do node
}

#endif UTILS_H	/* UTILS_H */
