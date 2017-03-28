#ifndef Local_H
#define Local_H


#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Local{
private:
	int id;		//TODO as ruas é que vao ter os nomes
	pair<float, float> coordinates;		//latitude, longitude
	int height;	//vai ser um numero aleatorio
public:
	Local(int id, pair<float, float> coord, int height);
	int getId() const;
	pair<float, float> getCoordinates() const;
	int getHeight() const;
	float getDistance(const Local & nd) const;
	bool operator ==(const Local & nd);
	void print();
};


#endif Local_H	/* Local_H */
