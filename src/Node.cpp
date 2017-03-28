#include "Node.h"

Node::Node(string name, pair<float, float> coord, float height){
	this->name = name;
	this->coordinates = coord;
	this->height = height;
}

string Node::getName() const{
	return name;
}

pair<float, float> Node::getCoordinates() const{
	return coordinates;
}

float Node::getHeight() const{
	return height;
}

float Node::getDistance(const Node & nd) const{
	return sqrt(pow(nd.getCoordinates().first - coordinates.first, 2) + pow(nd.getCoordinates().second - coordinates.second, 2) + pow(nd.getHeight() - height,2));
}

bool Node::operator ==(const Node & nd){
	if(coordinates == nd.getCoordinates() && height == nd.getHeight())
		return true;

	return false;
}

void Node::print(){
	cout << name << ": lat(" << coordinates.first << "); long(" << coordinates.second << "); height(" << height << ")\n";
}
