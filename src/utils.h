#ifndef UTILS_H
#define UTILS_H


#include <iostream>
#include "Graph.h"
#include "Local.h"
#include "graphviewer.h"

using namespace std;

void printMap(Graph<Local> &map){

	//TODO eventualmente por o mapa nao dynamic e definir eu as coordenadas dos pontos x,y de acordo com latitude e longitude
	//TODO definir com formas, icons, texto, cores diferentes nós especiais

	int idEdge = 0;
	GraphViewer gv(600, 600, true);
	gv.setBackground("background.jpg"); //TODO por no background print do bocado do mapa original correspondente às infos do ficheiro
	gv.createWindow(600, 600);
	gv.defineEdgeDashed(true);
	gv.defineVertexColor("blue");
	gv.defineEdgeColor("black");


	vector<Vertex<Local>* > vertexes = map.getVertexSet();
	for(size_t i = 0; i < vertexes.size(); i++){
		gv.addNode(vertexes.at(i)->getInfo().getId());
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

	Sleep(5000);
}

#endif UTILS_H	/* UTILS_H */
