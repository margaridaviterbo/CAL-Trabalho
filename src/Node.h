#ifndef NODE_H
#define NODE_H


#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Node{
private:
	string name;
	pair<float, float> coordinates;		//latitude, longitude
	float height;
public:
	Node(string name, pair<float, float> coord, float height);
	string getName() const;
	pair<float, float> getCoordinates() const;
	float getHeight() const;
	float getDistance(const Node & nd) const;
	bool operator ==(const Node & nd);
	void print();
};


#endif NODE_H	/* NODE_H */
