#include "Local.h"

Local::Local(long long id, pair<float, float> coord, int height){
	this->id = id;
	this->coordinates = coord;
	this->height = height;
}

long long Local::getId() const{
	return id;
}

pair<float, float> Local::getCoordinates() const{
	return coordinates;
}

int Local::getHeight() const{
	return height;
}

float Local::getWeight(const Local nd, int option) const{
	//enum de options
	//switch case para definir cada weight
	//distantia com x,y,h: sqrt(pow(nd.getCoordinates().first - coordinates.first, 2) + pow(nd.getCoordinates().second - coordinates.second, 2) + pow(nd.getHeight() - height,2));
}

map<long long, string> Local::getRoads(){
	return roads;
}

pair<bool, int> Local::getSharingPoint(){
	return sharingPoint;
}

void Local::setSharingPoint(pair<bool, int> sp){
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

void Local::addRoad(pair<long long, string> road) {
	roads.insert(road);
}

bool Local::setRoadName(long long roadId, string roadName){
	map<long long, string>::iterator it;
	it = roads.find(roadId);
	if(it != roads.end()) {
		it->second = roadName;
		return true;
	}
	return false;
}
