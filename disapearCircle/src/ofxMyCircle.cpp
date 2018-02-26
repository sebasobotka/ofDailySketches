#include "ofxMyCircle.h"

ofxMyCircle::ofxMyCircle() {
}

ofxMyCircle::~ofxMyCircle() {
}

void ofxMyCircle::setup(int id, float x, float y, float radius, ofColor circleColor) {
	this->id = id;
	this->circleX = x;
	this->circleY = y;
	this->circleRadius = radius;
	this->circleColor = circleColor;
}

void ofxMyCircle::draw() {
	ofSetColor(circleColor);
	ofDrawCircle(circleX, circleY, circleRadius);
	ofSetColor(255, 255, 255);
}

int ofxMyCircle::getId() const {
	return this->id;
}

float ofxMyCircle::getX() const {
	return this->circleX;
}

float ofxMyCircle::getY() const {
	return this->circleY;
}

float ofxMyCircle::getRadius() const {
	return this->circleRadius;
}

void ofxMyCircle::setPos(float x, float y) {
	this->circleX = x;
	this->circleY = y;
}