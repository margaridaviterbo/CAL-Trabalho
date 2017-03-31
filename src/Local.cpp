#include "Local.h"

Local::Local(int id, pair<float, float> coord, int height){
	this->id = id;
	this->coordinates = coord;
	this->height = height;
}

int Local::getId() const{
	return id;
}

pair<float, float> Local::getCoordinates() const{
	return coordinates;
}

int Local::getHeight() const{
	return height;
}

float Local::getDistance(const Local nd) const{
	return sqrt(pow(nd.getCoordinates().first - coordinates.first, 2) + pow(nd.getCoordinates().second - coordinates.second, 2) + pow(nd.getHeight() - height,2));
}

map<int, string> Local::getRoads(){
	return roads;
}

SharingPoint* Local::getSharingPoint(){
	return sharingPoint;
}

void Local::setSharingPoint(SharingPoint* sp){
	sharingPoint = sp;
}

bool Local::operator ==(const Local & nd){
	if(coordinates == nd.getCoordinates() && height == nd.getHeight())
		return true;

	return false;
}

void Local::print(){
	cout << id << ": lat(" << coordinates.first << "); long(" << coordinates.second << "); height(" << height << ")\n";
}
