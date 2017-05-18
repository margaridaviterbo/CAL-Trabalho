#include <iostream>

#include "Graph.h"
#include "MenusManager.h"
#include "Parsers.h"
#include <vector>
#include "Local.h"
#include "graphviewer.h"
#include "utils.h"
#include "Matcher.h"
using namespace std;

int main(){


	int city;

	cout << "\n\n\t\t\t\tWelcome to this BikeSharing Platform!\n\n";
	cout << "\t\t\t\t   Chose one of the following cities:\n";
	cout << "\t\t\t\t\t1 - SmallLand\n";
	cout << "\t\t\t\t\t2 - MediumLand\n";
	cout << "\t\t\t\t\t3 - Bigland\n";
	cout << "\n\t\t\t\t\tCITY: ";
	cin >> city;

	while(city < 1 || city > 3){
		cout << "\n\nInvalid city, try again: ";
		cin >> city;
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	displayMainMenu(city);



	return 0;
}
