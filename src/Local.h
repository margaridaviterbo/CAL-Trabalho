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
	long long id;
	pair<float, float> coordinates;		//latitude, longitude
	int height;
	map<long long, string> roads;		//idRoad, roadName
	SharingPoint* sharingPoint = NULL;
public:
	Local(long long id, pair<float, float> coord, int height);
	long long getId() const;
	pair<float, float> getCoordinates() const;
	int getHeight() const;
	float getDistance(const Local nd) const;
	SharingPoint* getSharingPoint();
	map<long long, string> getRoads();
	bool operator ==(const Local & nd);
	void print();
	void setSharingPoint(SharingPoint* sp);
	void addRoad(pair<long long, string> road);
	bool setRoadName(long long roadId, string roadName);
};


#endif Local_H	/* Local_H */
