#ifndef Local_H
#define Local_H


#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include "SharingPoint.h"

using namespace std;

enum searchOptions {SHORTEST_DIST, SHORTEST_HEIGHT, CLOSEST, DIST_DISCOUNT, HEIGHT_DISCOUNT, BIGGEST_DISCOUNT};

class Local{
private:
	long long id;
	pair<float, float> coordinates;		//latitude, longitude
	float diffDistCenter;
	int height;
	int diffHeightCenter;
	map<long long, string> roads;		//idRoad, roadName
	pair<bool, int> sharingPoint = pair<bool, int>(false, 0);	// is/is not sharingpoint, spots available
	bool userLocation = false;
	bool cityCenter = false;
public:
	Local(){};
	Local(long long id, pair<float, float> coord, int height);
	long long getId() const;
	pair<float, float> getCoordinates() const;
	float getDiffDistCenter() const;
	int getHeight() const;
	int getDiffHeightCenter() const;
	float getWeight(const Local nd, searchOptions op) const;
	pair<bool, int> getSharingPoint();
	bool getUserLocation();
	bool getCityCenter();
	map<long long, string> getRoads();
	bool operator ==(const Local & nd);
	void print();
	void setSharingPoint(pair<bool, int> sp);
	void setUserLocation();
	void setCityCenter();
	void setDiffHeightCenter(int diff);
	void setDiffDistCenter(float diff);
	void addRoad(pair<long long, string> road);
	bool setRoadName(long long roadId, string roadName);
};


#endif Local_H	/* Local_H */
