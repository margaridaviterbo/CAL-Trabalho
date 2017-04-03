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
	pair<bool, int> sharingPoint = pair<bool, int>(false, 0);	// is/is not sharingpoint, spots available
public:
	Local(long long id, pair<float, float> coord, int height);
	long long getId() const;
	pair<float, float> getCoordinates() const;
	int getHeight() const;
	float getWeight(const Local nd, int option) const;
	pair<bool, int> getSharingPoint();
	map<long long, string> getRoads();
	bool operator ==(const Local & nd);
	void print();
	void setSharingPoint(pair<bool, int> sp);
	void addRoad(pair<long long, string> road);
	bool setRoadName(long long roadId, string roadName);
};


#endif Local_H	/* Local_H */
