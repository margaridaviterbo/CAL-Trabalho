#ifndef Local_H
#define Local_H


#include <iostream>
#include <string>
#include <cmath>
#include <map>

using namespace std;

enum searchOptions {SHORTEST_DIST, SHORTEST_HEIGHT, CLOSEST, DIST_DISCOUNT, HEIGHT_DISCOUNT, BIGGEST_DISCOUNT};

class Local{
private:
	unsigned long long id;
	pair<float, float> coordinates;		//latitude, longitude
	float diffDistCenter;
	float height = 0;
	float diffHeightCenter = 0;
	map<unsigned long long, string> roads;		//idRoad, roadName
	pair<bool, int> sharingPoint = pair<bool, int>(false, 0);	// is/is not sharingpoint, spots available
	bool userLocation = false;
	bool cityCenter = false;
public:
	Local(){};
	Local(unsigned long long id, pair<float, float> coord, float height);
	unsigned long long getId() const;
	pair<float, float> getCoordinates() const;
	float getDiffDistCenter() const;
	float getHeight() const;
	float getDiffHeightCenter() const;
	double getWeight(const Local nd, searchOptions op) const;
	pair<bool, int> getSharingPoint();
	bool getUserLocation();
	bool getCityCenter();
	map<unsigned long long, string> getRoads();
	bool operator ==(const Local & nd);
	void print();
	void setSharingPoint(pair<bool, int> sp);
	void setUserLocation();
	void setCityCenter();
	void setDiffHeightCenter(float diff);
	void setDiffDistCenter(float diff);
	void addRoad(pair<long long, string> road);
	bool setRoadName(long long roadId, string roadName);
};


#endif Local_H	/* Local_H */
