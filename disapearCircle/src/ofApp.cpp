#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetCircleResolution(200);

	bigCircle.setup(1, 100, 100, 50, ofColor(255, 195, 22));

	shared_ptr<ofxMyCircle> circ1 = shared_ptr<ofxMyCircle>(new ofxMyCircle);
	circ1->setup(2, 120, 80, 20, ofColor().red);
	circles.emplace_back(circ1);
	shared_ptr<ofxMyCircle> circ2 = shared_ptr<ofxMyCircle>(new ofxMyCircle);
	circ2->setup(3, 200, 80, 20, ofColor().green);
	circles.emplace_back(circ2);
	shared_ptr<ofxMyCircle> circ3 = shared_ptr<ofxMyCircle>(new ofxMyCircle);
	circ3->setup(4, 280, 80, 20, ofColor().blue);
	circles.emplace_back(circ3);
	
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(0);

	for (const auto & c : circles) {
		c.get()->draw();
	}
	bigCircle.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

	bigCircle.setPos(x, y);

	for (int i = 0; i< circles.size();i++) {
		if ((ofDist(bigCircle.getX(), bigCircle.getY(), circles[i].get()->getX(), circles[i].get()->getY()) < (bigCircle.getRadius() + circles[i].get()->getRadius()))) {
			ofLogNotice("over circle") << circles[i].get()->getId();
			circles.erase(circles.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::exit() {
}