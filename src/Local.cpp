#include "Local.h"

Local::Local(unsigned long long id, int UXid, pair<float, float> coord, float height){
	this->id = id;
	this-> UXid = UXid;
	this->coordinates = coord;
	this->height = height;
}

unsigned long long Local::getId() const{
	return id;
}

int Local::getUXid(){
	return UXid;
}

pair<float, float> Local::getCoordinates() const{
	return coordinates;
}

float Local::getDiffDistCenter() const{
	return diffDistCenter;
}

float Local::getHeight() const{
	return height;
}

float Local::getDiffHeightCenter() const{
	return diffHeightCenter;
}

double Local::getWeight(const Local nd, searchOptions op){

	switch (op) {

	case SHORTEST_DIST:
		return sqrt(pow(nd.getCoordinates().first - coordinates.first, 2) + pow(nd.getCoordinates().second - coordinates.second, 2));

	case SHORTEST_HEIGHT:
		return abs(nd.getHeight() - height);

	case CLOSEST:
		return sqrt(pow(nd.getCoordinates().first - coordinates.first, 2) + pow(nd.getCoordinates().second - coordinates.second, 2) + pow(nd.getHeight() - height,2));

	case DIST_DISCOUNT:
		if(abs(nd.getDiffDistCenter() - diffDistCenter) == 0){
			return 10000;
		}
		return 1/(abs(nd.getDiffDistCenter() - diffDistCenter));

	case HEIGHT_DISCOUNT:
		if(abs(nd.getDiffHeightCenter() - diffHeightCenter) == 0){
			return 10000;
		}
		return 1/(abs(nd.getDiffHeightCenter() - diffHeightCenter));

	case BIGGEST_DISCOUNT:
		if(sqrt(pow(nd.getDiffDistCenter() - getDiffDistCenter(), 2) + pow(nd.getDiffHeightCenter() - diffHeightCenter, 2)) == 0){
			return 10000;
		}
		return 1/(sqrt(pow(nd.getDiffDistCenter() - getDiffDistCenter(), 2) + pow(nd.getDiffHeightCenter() - diffHeightCenter, 2)));
	}
	return -1;
}

map<unsigned long long, string> Local::getRoads(){
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

void Local::setDiffHeightCenter(float diff){
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
	map<unsigned long long, string>::iterator it;
	it = roads.find(roadId);
	if(it != roads.end()) {
		it->second = roadName;
		return true;
	}
	return false;
}
