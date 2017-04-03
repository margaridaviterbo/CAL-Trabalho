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

float Local::getDiffDistCenter() const{
	return diffDistCenter;
}

int Local::getHeight() const{
	return height;
}

int Local::getDiffHeightCenter() const{
	return diffHeightCenter;
}

float Local::getWeight(const Local nd, searchOptions op) const{

	switch (op) {

	case SHORTEST_DIST:
		return sqrt(pow(nd.getCoordinates().first - coordinates.first, 2) + pow(nd.getCoordinates().second - coordinates.second, 2));

	case SHORTEST_HEIGHT:
		return abs(nd.getHeight() - height);

	case CLOSEST:
		return sqrt(pow(nd.getCoordinates().first - coordinates.first, 2) + pow(nd.getCoordinates().second - coordinates.second, 2) + pow(nd.getHeight() - height,2));

	case DIST_DISCOUNT:
		return abs(nd.getDiffDistCenter() - diffDistCenter);

	case HEIGHT_DISCOUNT:
		return abs(nd.getDiffHeightCenter() - diffHeightCenter);

	case BIGGEST_DISCOUNT:
		return sqrt(pow(nd.getDiffDistCenter() - getDiffDistCenter(), 2) + pow(nd.getDiffHeightCenter() - diffHeightCenter, 2));

	}
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

bool Local::getUserLocation(){
	return userLocation;
}

bool Local::getCityCenter(){
	return cityCenter;
}

void Local::setUserLocation(){
	userLocation = true;
}

void Local::setCityCenter(){
	cityCenter = true;
}

void Local::setDiffDistCenter(float diff){
	diffDistCenter = diff;
}

void Local::setDiffHeightCenter(int diff){
	diffHeightCenter = diff;
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
