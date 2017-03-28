#ifndef PARSERS_H
#define PARSERS_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "Local.h"
#include "Graph.h"

using namespace std;

void readLocals(Graph<Local> &map){
	string line, data;
	int id;
	float lat, longi;
	int height;
	ifstream localsFile("files/A.txt");

	if(localsFile.is_open()){
		while(getline(localsFile, line)){
			stringstream ss(line);
			getline(ss, data, ';');
			id = atoi(data.c_str());
			getline(ss, data, ';');
			lat = atof(data.c_str());
			getline(ss, data, ';');
			longi = atof(data.c_str());
			height = rand() % 1001;
			pair<float, float> coord(lat, longi);
			Local local(id, coord, height);
			map.addVertex(local);
		}
	}
	else
		cout << "Could not open A.txt!\n";

}

void readStreets(Graph<Local> &map){

}

#endif PARSERS_H	/* PARSERS_H */
