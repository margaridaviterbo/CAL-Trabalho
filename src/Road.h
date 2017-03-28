#ifndef ROAD_H
#define ROAD_H


#include <iostream>
#include <string>
#include "Local.h"

using namespace std;

class Road{
private:
	int id;
	string name;
	Local local1, local2;
	float length;
	bool twoWays = false;
public:
	Road(int id, Local local1, Local local2);
	void setName(string name);
	void setTwoWays();
	int getId();
};


#endif ROAD_H	/* ROAD_H */
