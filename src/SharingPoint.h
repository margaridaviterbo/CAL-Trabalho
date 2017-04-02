#ifndef SHARINGPOINT_H
#define SHARINGPOINT_H


#include <iostream>
#include <cstdlib>

using namespace std;

class SharingPoint{
private:
	int numFreeSpots;
	bool heightDiscount = false;
	bool suburbsDiscount = false;
public:
	SharingPoint();
	int getNumFreeSpots();
	bool getHeightDiscount();
	bool getSuburbsDiscount();
	void updateFreeSpots();
	void setHeightDiscount();
	void setSuburbsDiscount();
};


#endif SHARINGPOINT_H	/* SHARINGPOINT_H */
