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

void readStreets(Graph<Local> &map){

	string line, data;
	int roadId, local1Id, local2Id;
	bool exists;

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

			if(l1.getRoads().find(roadId) == l1.getRoads().end())
				l1.getRoads().insert(pair<int, string> (roadId, ""));
		}
	}
	else
		cout << "Could not open C.txt!\n";	//TODO mudar mensagem para especificar ficheiro direito
}

void readRoadsDirections(Graph<Local> &mapa){
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

			for(size_t i = 0; i < mapa.getVertexSet().size(); i++){
				map<int, string>::iterator it = mapa.getVertexSet().at(i)->getInfo().getRoads().begin();
				map<int, string>::iterator it_e = mapa.getVertexSet().at(i)->getInfo().getRoads().end();
				while(it != it_e){
					if(it->first == roadId)
						it->second = roadName;
					it++;
				}

				if(data == "True"){		//percorrer vetor adjacentes de cada vertex e de forem ambos da rua roadId verificar que tem duas ligaçoes
					roads.at(i).setTwoWays();
					map.addEdge(*(roads.at(i).getLocal2()), *(roads.at(i).getLocal1()), roads.at(i).getLength());
				}

			}
		}
	}
	else
		cout << "Could not open B.txt!\n";	//TODO mudar mensagem para especificar ficheiro direito

}
#endif PARSERS_H	/* PARSERS_H */
