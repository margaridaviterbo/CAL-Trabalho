#ifndef PARSERS_H
#define PARSERS_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "Local.h"
#include "Road.h"
#include "Graph.h"

using namespace std;

void readLocals(Graph<Local> &map){
	string line, data;
	int id;
	float lat, longi;
	int height;
	ifstream localsFile("files/A.txt");		//TODO mudar para receber ficheiro com a regiao a analizar

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
		cout << "Could not open A.txt!\n";	//TODO mudar mensagem para especificar ficheiro direito

}

void readStreets(Graph<Local> &map, vector<Road> &roads){

	string line, data;
	int roadId, local1Id, local2Id;

	ifstream roadsFile("files/C.txt");		//TODO mudar para receber ficheiro com a regiao a analizar

	if(roadsFile.is_open()){
		while(getline(roadsFile, line)){
			stringstream ss(line);
			getline(ss, data, ';');
			roadId = atoi(data.c_str());
			getline(ss, data, ';');
			local1Id = atoi(data.c_str());
			getline(ss, data, ';');
			local2Id = atoi(data.c_str());
			Local l1 = map.getLocal(local1Id);
			Local l2 = map.getLocal(local2Id);
			map.addEdge(l1, l2, l1.getDistance(l2));
			Road r(roadId, &l1, &l1);
			roads.push_back(r);
		}
	}
	else
		cout << "Could not open C.txt!\n";	//TODO mudar mensagem para especificar ficheiro direito
}

void readRoadsDirections(Graph<Local> &map, vector<Road> &roads){
	string line, data;
	int roadId;
	string roadName;

	ifstream directionsFile("files/B.txt");		//TODO mudar para receber ficheiro com a regiao a analizar

	if(directionsFile.is_open()){
		while(getline(directionsFile, line)){
			stringstream ss(line);
			getline(ss, data, ';');
			roadId = atoi(data.c_str());
			getline(ss, data, ';');
			roadName = atoi(data.c_str());
			getline(ss, data, '\n');

			for(unsigned int i = 0; i < roads.size(); i++){
				if(roads.at(i).getId() == roadId){
					roads.at(i).setName(roadName);
					if(data == "True"){
						roads.at(i).setTwoWays();
						map.addEdge(*(roads.at(i).getLocal2()), *(roads.at(i).getLocal1()), roads.at(i).getLength());
					}
				}
			}
		}
	}
	else
		cout << "Could not open B.txt!\n";	//TODO mudar mensagem para especificar ficheiro direito

}
#endif PARSERS_H	/* PARSERS_H */
