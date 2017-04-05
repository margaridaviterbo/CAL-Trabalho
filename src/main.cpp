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

	cout << "\n\n\t\t\t\tWelcome to this BikeSharing Platform!\n\n\n";
	displayMainMenu(cityMap);



	return 0;
}
