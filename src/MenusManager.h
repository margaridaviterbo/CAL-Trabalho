#ifndef MENUSMANAGER
#define MENUSMANAGER


#include <iostream>
#include "utils.h"
#include "Graph.h"
#include "graphviewer.h"

using namespace std;

void displayMainMenu(Graph<Local> &map){
	printMap(map);	//TODO isto vai ser chamado só quando o user escolher o criterio e der a sua localizaçao para obter o caminho
}

#endif MENUSMANAGER	/* MENUSMANAGER */
