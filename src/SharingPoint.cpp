#include "SharingPoint.h"

SharingPoint::SharingPoint(){
	numFreeSpots = rand () % 6;
}

int SharingPoint::getNumFreeSpots(){
	return numFreeSpots;
}

bool SharingPoint::getHeightDiscount(){
	return heightDiscount;
}

bool SharingPoint::getSuburbsDiscount(){
	return suburbsDiscount;
}

void SharingPoint::updateFreeSpots(){
	numFreeSpots--;
}

void SharingPoint::setHeightDiscount(){
	heightDiscount = true;
}

void SharingPoint::setSuburbsDiscount(){
	suburbsDiscount = true;
}
