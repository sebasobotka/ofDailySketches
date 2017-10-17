#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

#define APP_VER "fractaltree recursive 0.01"

class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void exit();
		void setDefault();
		void savePrintedImg();
		void setupGui();

		void onDropdownEvent(ofxDatGuiDropdownEvent e);
		void onToggleEvent(ofxDatGuiToggleEvent e);
		void onTextInputEvent(ofxDatGuiTextInputEvent e);
		void onButtonEvent(ofxDatGuiButtonEvent e);
		void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
		void onSliderEvent(ofxDatGuiSliderEvent e);

		void drawBranch(int length);
		void drawLeaf(int x, int y);

private:
		ofFbo recordFbo;
		ofxDatGui* datGui; 
		bool bShowGui = true;
		int appFrameRate = 60;
		int appWidth = 1920;
		int appHeight = 1080;
	
		float lineWidth = 2;
		float lineLen = 300;
		int bothAngle = 45;
		int rightBranchAngle = 45;
		int leftBranchAngle = 45;
		float lineLenCut = 0.63;
		bool bDrawLeaf = true;
		bool bFillLeaf = false;
		int leafRad = 2;
		ofColor bckgroundColor = ofColor(0, 0, 0);
		ofColor lineColor = ofColor(255, 255, 255);
		ofColor leafColor = ofColor(255, 0, 0);
};
