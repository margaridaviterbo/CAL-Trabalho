#ifndef PARSERS_H
#define PARSERS_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iterator>
#include "Local.h"
#include "Graph.h"
#include "graphviewer.h"

using namespace std;

void readLocals(Graph<Local> &map, vector<float> heights, vector<pair<int, int> > sharingPoints){

	string line, data;
	unsigned long long id;
	float lat, longi;
	float height;
	ifstream localsFile("files/A2.txt");		//TODO mudar para receber ficheiro com a regiao a analizar

	if(localsFile.is_open()){
		int i = 0;
		while(getline(localsFile, line)){
			stringstream ss(line);
			getline(ss, data, ';');
			id = strtoull(data.c_str(), NULL, 10);
			getline(ss, data, ';');
			lat = atof(data.c_str());
			getline(ss, data, ';');
			longi = atof(data.c_str());
			if(heights.size() == 0){
				height = rand() % 11;
			}
			else
				height = heights.at(i);
			pair<float, float> coord(lat, longi);
			Local local(id, coord, height);
			if(sharingPoints.size() != 0){
				if(sharingPoints.at(i).first == 1)
					local.setSharingPoint(pair<bool, int>(true, sharingPoints.at(i).second));
			}
			map.addVertex(local);
			i++;
		}
	}
	else
		cout << "Could not open A.txt!\n";	//TODO mudar mensagem para especificar ficheiro direito

}

void readStreets(Graph<Local> &mapa, searchOptions op){

	string line, data;
	unsigned long long roadId, local1Id, local2Id;
	bool exists;

	ifstream roadsFile("files/C2.txt");		//TODO mudar para receber ficheiro com a regiao a analizar

	if(roadsFile.is_open()){
		while(getline(roadsFile, line)){
			stringstream ss(line);
			getline(ss, data, ';');
			roadId = strtoull(data.c_str(), NULL, 10);
			getline(ss, data, ';');
			local1Id = strtoull(data.c_str(), NULL, 10);
			getline(ss, data, ';');
			local2Id = strtoull(data.c_str(), NULL, 10);
			Local *l1 = mapa.getLocal(local1Id);
			Local *l2 = mapa.getLocal(local2Id);
			mapa.addEdge(*(l1), *(l2), l1->getWeight(*l2, op));

			if(l1->getRoads().count(roadId) == 0) {
				l1->addRoad(pair<unsigned long long, string>(roadId, ""));
			}
			if(l2->getRoads().count(roadId) == 0){
				l2->addRoad(pair<unsigned long long, string>(roadId, ""));
			}
		}
	}
	else
		cout << "Could not open C.txt!\n";	//TODO mudar mensagem para especificar ficheiro direito
}

void readRoadsDirections(Graph<Local> &mapa, searchOptions op){
	string line, data;
	unsigned long long roadId;
	string roadName;
	bool connection;

	ifstream directionsFile("files/B2.txt");		//TODO mudar para receber ficheiro com a regiao a analizar

	if(directionsFile.is_open()){
		while(getline(directionsFile, line)){
			stringstream ss(line);
			getline(ss, data, ';');
			roadId = strtoull(data.c_str(), NULL, 10);
			getline(ss, data, ';');
			roadName = data;
			getline(ss, data, '\n');

			for (size_t i = 0; i < mapa.getVertexSet().size(); i++){
				unsigned long long localId = mapa.getVertexSet().at(i)->getInfo().getId();
				Local *l1 = mapa.getLocal(localId);
				l1->setRoadName(roadId, roadName);

				if(data == "True"){
					vector<Edge<Local> > adjacents_origin = mapa.getVertexSet().at(i)->getAdj();
					for(size_t j=0; j < adjacents_origin.size(); j++){
						Local node_adj = adjacents_origin.at(j).getDest()->getInfo();
						if(node_adj.getRoads().find(roadId) != node_adj.getRoads().end()){
							connection = false;
							vector<Edge<Local> > adjacents_dest = mapa.getVertexSet().at(i)->getAdj().at(j).getDest()->getAdj();
							for(size_t k=0; k < adjacents_dest.size(); k++){
								if(adjacents_dest.at(k).getDest() == mapa.getVertexSet().at(i))
									connection = true;
							}
							if(connection == false)
								mapa.addEdge(node_adj, mapa.getVertexSet().at(i)->getInfo(), adjacents_origin.at(j).getWeight());
						}
					}
				}
			}
		}
	}
	else
		cout << "Could not open B.txt!\n";	//TODO mudar mensagem para especificar ficheiro direito

}
#endif PARSERS_H	/* PARSERS_H */
