#ifndef Local_H
#define Local_H


#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include "SharingPoint.h"

using namespace std;

class Local{
private:
	int id;
	pair<float, float> coordinates;		//latitude, longitude
	int height;
	map<int, string> roads;		//idRoad, roadName
	SharingPoint* sharingPoint = NULL;
public:
	Local(int id, pair<float, float> coord, int height);
	int getId() const;
	pair<float, float> getCoordinates() const;
	int getHeight() const;
	float getDistance(const Local nd) const;
	SharingPoint* getSharingPoint();
	map<int, string> getRoads();
	bool operator ==(const Local & nd);
	void print();
	void setSharingPoint(SharingPoint* sp);
	void addRoad(pair<int, string> road);
	bool setRoadName(int roadId, string roadName);
};


#endif Local_H	/* Local_H */
