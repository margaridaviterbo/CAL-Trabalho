#ifndef MENUSMANAGER
#define MENUSMANAGER


#include <iostream>
#include "utils.h"
#include "Graph.h"
#include "graphviewer.h"
#include "Matcher.h"

Graph<Local> mapa;

using namespace std;

void findSharingPointMenu(Graph<Local> &map, int city);
void searchByStreetName(int city);


/**
 * função que faz o display do menu principal
 * @param city é o identificador da cidade sobre a qual deve ser gerado o mapa
 */
void displayMainMenu(int city){
	int op;

	cout << "\t\t\t====================================================" << endl;
	cout << "\t\t\t|		(1) SEE CITY MAP		   |" << endl;
	cout << "\t\t\t====================================================" << endl << endl << endl;
	cout << "\t\t\t====================================================" << endl;
	cout << "\t\t\t|	(2) SEARCH BIKE SHARING POINT	    	   |" << endl;
	cout << "\t\t\t====================================================" << endl << endl << endl;
	cout << "\t\t\t====================================================" << endl;
	cout << "\t\t\t|		(3) SEARCH BY STREET	   	   |" << endl;
	cout << "\t\t\t====================================================" << endl << endl << endl;
	cout << "Please chose an option(press 0 to exit): ";
	do{
		cin >> op;
		cout << endl;
		if(op != 1 && op != 2 && op != 3)
			cout << "Invalid option, chose between 1 or 2: ";
	}while(op != 1 && op != 2 && op != 3);

	Graph<Local> tempMap;

	if(op == 1){
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		builtGraph(tempMap, SHORTEST_DIST, city);
		vector<int> p;
		p.push_back(-1);
		printMap(tempMap, -1, p);
	}
	else if(op == 2){
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		findSharingPointMenu(tempMap, city);
	}
	else if(op == 3){
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		searchByStreetName(city);
	}
	else{
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		exit(0);
	}

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	displayMainMenu(city);
}


/**
 * função que faz o display do menu com as opçoes para encontrar um ponto de partinha
 * @param map é o grafo que representa o mapa da cidade
 * @param city é o identificador da cidade sobre a qual se vao construir o grafo
 */
void findSharingPointMenu(Graph<Local> &map, int city){
	int op;
	searchOptions option;
	int id;
	Graph<Local> tempMap;
	builtGraph(tempMap, SHORTEST_DIST, city);

	cout << "Enter the ID of your location (to see the map with IDs press 0): ";
	cin >> id;

	if(id == 0){
		vector<int> p;
		p.push_back(-1);
		printMap(tempMap, -1, p);
		cout << "Enter the ID of your location: ";
		cin >> id;
	}

	if(id > 0 && id < (int)tempMap.getVertexSet().size()){

		cout << "Chose your criteria to find a Sharing Point:" << endl << endl;
		cout << "1 - Least plain distance\n";
		cout << "2 - Least vertical distance\n";
		cout << "3 - Closest to me\n";
		cout << "4 - With discount (based on distance to center)\n";
		cout << "5 - With discount (based on difference of height from center)\n";
		cout << "6 - Biggest discount\n";
		cout << "Option: ";
		cin >> op;

		do{
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
				break;
			}

		}while (op < 1 || op > 6);

		builtGraph(map, option, city);
		vector<int> path = map.findShortestPath(*map.getLocal(id - 1), op);		//passar aqui node da loclizaçao do user
		printMap(map, id, path);


	}
	else{
		cout << "That local does not exist.\n";
	}
}


void searchByStreetName(int city){
	int op, option;
	string streetName, street;
	Graph<Local> tempMap;
	builtGraph(tempMap, SHORTEST_DIST, city);
	vector<string> strings;
	vector<string> streets;

	int i = 0;
	while(streets.size() < 2){

		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		cout << "Chose the type of search you want to use for street " << i+1 << ":" << endl << endl;
		cout << "1 - Exact Search (searches for the exact expression you use - CASE SENSITIVE)\n";
		cout << "2 - Approximate Search (searches for similar expressions to the one you use)\n";
		cout << "Option: ";
		cin >> op;

		while (op != 1 && op != 2){
			cin.clear();
			cin.ignore(256, '\n');
			cout << endl << endl <<"INVALID OPTION! Please try again: ";
			cin >> op;
		}


		cout << endl << "Enter street " << i+1 << " name: ";

		cin.clear();
		cin.ignore(256, '\n');
		getline(cin, streetName);

		if(op == 1){

			strings = exactSearch(streetName, tempMap);
			char opt;
			if(strings.size() == 0){
				cout << endl << "Unknown street." << endl;
				cout << endl << "Press 1 to search again (any other key to return to main menu): ";
				cin >> opt;
				if(opt != '1'){
					return;
				}
			}

			if(strings.size() != 0){

				do{
					cout << endl << "Which of the following streets are you looking for? (enter number) " << endl << "0 - NO STREET MATCHES MY SEARCH\n\n";

					for(int j = 0; j < (int)strings.size(); j++){
						cout << j + 1 << " - " << strings.at(j) << endl;
					}
					cout << "Option: ";
					cin >> option;

					if(option < 0 || option > (int)strings.size()){
						cout << "INVALID OPTION!" << endl;
					}

				}while(option < 0 || option > (int)strings.size());

				if(option != 0){
					streets.push_back(strings.at(option - 1));
					i++;
				}
			}
		}


		else{
			strings = approximateSearch(streetName, tempMap);

			do{
				cout << endl << "Search results are ordered by similarity to the data you entered." << endl;
				cout << "Which of the following streets are you looking for? (enter number) " << endl << "0 - NO STREET MATCHES MY SEARCH\n\n";

				for(int j = 0; j < (int)strings.size(); j++){
					cout << j + 1 << " - " << strings.at(j) << endl;
				}
				cout << "Option: ";
				cin >> option;

				if(option < 0 || option > (int)strings.size()){
					cout << "INVALID OPTION!" << endl;
				}

			}while(option < 0 || option > (int)strings.size());

			if(option != 0){
				streets.push_back(strings.at(option - 1));
				i++;
			}
		}

	}

	Local sharingPoint = findCrossroad(streets, tempMap);
	if(sharingPoint.getId() != (unsigned long long)(-1)){
		if(sharingPoint.getSharingPoint().first){
			cout << endl << endl << "There is a Sharing Point with " << sharingPoint.getSharingPoint().second << " spots available in the crossroad between the streets you searched.\n";
		}
		else{
			cout << endl << endl << "There's not a Sharing Point in the crossroad between the streets you searched.\n";
		}
	}
	else{
		cout << endl << "The streets you searched do not cross.\n";
	}


	cout << "sharingPoint.getId() " << sharingPoint.getId() << "sharingPoint.getSharingPoint() " << sharingPoint.getSharingPoint().first << endl;

	cin.clear();
	cin.ignore(256, '\n');
	do{
		cout << '\n' << "Press enter to continue...";
	} while (cin.get() != '\n');

}


#endif MENUSMANAGER	/* MENUSMANAGER */
