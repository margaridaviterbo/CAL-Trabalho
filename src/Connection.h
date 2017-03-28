#ifndef CONNECTION_H
#define CONNECTION_H


#include <iostream>
#include <string>
#include "Local.h"

using namespace std;

class Connection{
private:
	int roadId;
	string roadName;
	Local *local1, *local2;
	float length;
public:
	Connection(int id, Local* local1, Local* local2);
	void setName(string name);
	int getRoadId();
	Local* getLocal1();
	Local* getLocal2();
	float getLength();
};


#endif CONNECTION_H	/* CONNECTION_H */

