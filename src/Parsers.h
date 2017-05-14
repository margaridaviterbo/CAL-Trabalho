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

/**
 * função que faz parsing das informações sobre os nodes que estão no ficheiro txt
 * @param map refere se ao grafo que representa o mapa da cidade
 * @param heights é o vetor com alturas random para os locais pre-definidas
 * @param sharingPoints é o vetor que é utilizado para atribuir aleatoriamente os pontos de partilha
 * @file é o parametro que contem o nome do ficheiro a partir do qual ler a informaçao
 */
void readLocals(Graph<Local> &map, vector<float> heights, vector<pair<int, int> > sharingPoints, string file){
	int UXid = 1;
	string line, data;
	unsigned long long id;
	float lat, longi;
	float height;
	ifstream localsFile(file.c_str());

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
			Local local(id, UXid, coord, height);
			UXid++;
			if(sharingPoints.size() != 0){
				if(sharingPoints.at(i).first == 1)
					local.setSharingPoint(pair<bool, int>(true, sharingPoints.at(i).second));
			}
			map.addVertex(local);
			i++;
		}
	}
	else
		cout << "Could not open " << file << " !\n";

}


/**
 * função que faz parsing das informações sobre as conexões entre os nodes que estão no ficheiro txt
 * @param map refere se ao grafo que representa o mapa da cidade
 * @param op contem o identificador da opçao de pesquisa escolhida pelo user
 * @file é o parametro que contem o nome do ficheiro a partir do qual ler a informaçao
 */
void readStreets(Graph<Local> &mapa, searchOptions op, string file){

	string line, data;
	unsigned long long roadId, local1Id, local2Id;
	bool exists;

	ifstream roadsFile(file.c_str());

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
		cout << "Could not open " << file << " !\n";
}

/**
 * função que faz parsing das informações sobre os sentidos das conexoes e nomes das ruas que estão no ficheiro txt
 * @param map refere se ao grafo que representa o mapa da cidade
 * @param op contem o identificador da opçao de pesquisa escolhida pelo user
 * @file é o parametro que contem o nome do ficheiro a partir do qual ler a informaçao
 */
void readRoadsDirections(Graph<Local> &mapa, searchOptions op, string file){
	string line, data;
	unsigned long long roadId;
	string roadName;
	bool connection;

	ifstream directionsFile(file.c_str());

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
				mapa.getLocal(localId)->setRoadName(roadId, roadName);

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
		cout << "Could not open " << file << " !\n";
}
#endif PARSERS_H	/* PARSERS_H */
