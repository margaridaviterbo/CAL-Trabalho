#ifndef Local_H
#define Local_H


#include <iostream>
#include <string>
#include <cmath>
#include <map>

using namespace std;

class Local{
private:
	int id;
	pair<float, float> coordinates;		//latitude, longitude
	int height;
	map<int, string> roads;		//idRoad, roadName
public:
	Local(int id, pair<float, float> coord, int height);
	int getId() const;
	pair<float, float> getCoordinates() const;
	int getHeight() const;
	float getDistance(const Local nd) const;
	map<int, string> getRoads();
	bool operator ==(const Local & nd);
	void print();

	bool isDeliveryPoint=false;		//TODO para apagar
};


#endif Local_H	/* Local_H */
