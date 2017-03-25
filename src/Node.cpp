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

bool Node::operator ==(const Node & nd){
	if(coordinates == nd.getCoordinates() && height == nd.getHeight())
		return true;

	return false;

}
