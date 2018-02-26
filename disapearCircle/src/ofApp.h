#pragma once

#include "ofMain.h"
#include "ofxMyCircle.h"

class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseMoved(int x, int y);
		void exit();


private:
		ofxMyCircle circle1;
		ofxMyCircle circle2;
		ofxMyCircle circle3;
		ofxMyCircle bigCircle;

		std::vector<shared_ptr<ofxMyCircle>> circles;
		
};
