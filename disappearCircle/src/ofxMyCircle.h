#pragma once
#include "ofMain.h"

class ofxMyCircle {
public:
	ofxMyCircle();
	~ofxMyCircle();
	
	// methods
	void setup(int id, float x, float y, float radius, ofColor circleColor);
	void draw();
	int getId() const;
	float getX() const;
	float getY() const;
	float getRadius() const;
	void setPos(float x, float y);

private:
	int id;
	float circleX;
	float circleY;
	float circleRadius;
	ofColor circleColor;
};
