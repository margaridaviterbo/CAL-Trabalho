#include <iostream>

#include "Graph.h"
#include "MenusManager.h"
#include "Parsers.h"
#include <vector>
#include "Local.h"
#include "graphviewer.h"
#include "utils.h"
using namespace std;

Graph<Local> cityMap;

int main(){

	cout << "Welcome to this BikeSharing Platform!";
	displayMainMenu(cityMap);



	return 0;
}
