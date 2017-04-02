#ifndef UTILS_H
#define UTILS_H


#include <iostream>
#include "Graph.h"
#include "Local.h"
#include "graphviewer.h"

using namespace std;

void printMap(Graph<Local> &map, GraphViewer &gv){

	//TODO eventualmente por o mapa nao dynamic e definir eu as coordenadas dos pontos x,y de acordo com latitude e longitude

	gv.setBackground("background.jpg");
	gv.createWindow(600, 600);
	gv.defineEdgeDashed(true);
	gv.defineVertexColor("blue");
	gv.defineEdgeColor("black");

	//TODO definir com formas, icons, texto, cores diferentes nós especiais



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
