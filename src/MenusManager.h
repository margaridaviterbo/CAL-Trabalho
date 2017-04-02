#ifndef MENUSMANAGER
#define MENUSMANAGER


#include <iostream>
#include "utils.h"
#include "Graph.h"
#include "graphviewer.h"

using namespace std;

void displayMainMenu(Graph<Local> &map, GraphViewer &gv){
	printMap(map, gv);
}

#endif MENUSMANAGER	/* MENUSMANAGER */
