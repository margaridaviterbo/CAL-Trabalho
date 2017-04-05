#ifndef MENUSMANAGER
#define MENUSMANAGER


#include <iostream>
#include "utils.h"
#include "Graph.h"
#include "graphviewer.h"

using namespace std;

void displayMainMenu(Graph<Local> &map){
	int op;
	searchOptions option;

	cout << "Chose your criteria to find a Sharing Point:" << endl << endl;
	cout << "1 - Least plain distance\n";
	cout << "2 - Least vertical distance\n";
	cout << "3 - Closest to me\n";
	cout << "4 - With discount (based on distance to center)\n";
	cout << "5 - With discount (based on difference of height from center)\n";
	cout << "6 - Biggest discount\n";
	cout << "Option: ";
	cin >> op;

	while (op < 1 || op > 6){
		switch (op){
		case 1:
			option = SHORTEST_DIST;
			break;

		case 2:
			option = SHORTEST_HEIGHT;
			break;

		case 3:
			option = CLOSEST;
			break;

		case 4:
			option = DIST_DISCOUNT;
			break;

		case 5:
			option = HEIGHT_DISCOUNT;
			break;

		case 6:
			option = BIGGEST_DISCOUNT;
			break;

		default:
			cout << "INVALID OPTION! Please try again: ";
			cin >> op;
		}
	}

	builtGraph(map, option);
	printMap(map);
}

#endif MENUSMANAGER	/* MENUSMANAGER */
