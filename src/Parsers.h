#ifndef PARSERS_H
#define PARSERS_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

void readLocals(){
	string line, data;
	int id;
	float lat, longi;
	int height;
	ifstream localsFile("files/A.txt");

	if(localsFile.is_open()){
		while(getline(localsFile, line)){
			stringstream ss(line);
			getline(ss, data, ';');
			id = (int)data;
			getline(ss, data, ';');
			lat = (float)data;
			getline(ss, data, ';');
			longi = (float)data;
			height = rand() % 1001;
			Node()
		}
	}
	else
		cout << "Could not open A.txt!\n";

}

void readStreets(){

}

#endif PARSERS_H	/* PARSERS_H */
