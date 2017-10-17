#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	
	//ofSetVerticalSync(true);

	setupGui();
	ofSetFrameRate(appFrameRate);
	ofSetWindowShape(appWidth, appHeight);

	ofSetCircleResolution(200);
	
	// for recording
	recordFbo.allocate(appWidth, appHeight, GL_RGB);
	recordFbo.begin();
	ofClear(0, 0, 0, 255);
	recordFbo.end();
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(bckgroundColor);
	
	recordFbo.begin();
		//ofClear(0, 0, 0, 255);
		ofClear(bckgroundColor);

		ofPushMatrix();
		ofTranslate(appWidth / 2, appHeight);
		ofSetLineWidth(lineWidth);
		drawBranch(lineLen);
		ofPopMatrix();

	recordFbo.end();
	
	recordFbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::exit() {
}

//--------------------------------------------------------------
void ofApp::savePrintedImg() {
	ofPixels pix;
	string saveFileName;

	char strTime[26];
	struct tm* tmInfo;
	time_t rawtime;
	time(&rawtime);
	tmInfo = localtime(&rawtime);
	strftime(strTime, 26, "%Y_%m_%d_%H_%M_%S", tmInfo);
	saveFileName = "screen_" + ofToString(strTime);

	recordFbo.readToPixels(pix);
	ofSaveImage(pix, "images/" + saveFileName + "_" + ofToString(ofGetFrameNum()) + ".jpg", OF_IMAGE_QUALITY_BEST);

	// save parameters to file
	//settings.saveFile("images/" + saveFileName + ".xml");
}

//--------------------------------------------------------------
void ofApp::setupGui() {
	datGui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	
	datGui->addHeader(":: drag me to reposition ::");
	datGui->addFRM();
	datGui->addTextInput("version", APP_VER);
	datGui->addBreak();

	datGui->addSlider("line length", 0, appHeight / 2, lineLen);
	datGui->addSlider("line length cut", 0, 0.78, lineLenCut);
	datGui->addSlider("line width", 0, 10.0, lineWidth);
	
	datGui->addSlider("angle", 0, 180, bothAngle);
	datGui->addSlider("left angle", 0, 180, leftBranchAngle);
	datGui->addSlider("right angle", 0, 180, rightBranchAngle);
	datGui->addColorPicker("line color", lineColor);
	
	
	datGui->addBreak();
	datGui->addToggle("draw leaf", bDrawLeaf);
	datGui->addToggle("fill leaf", bFillLeaf);
	datGui->addSlider("leaf radius", 0, 30, leafRad);
	datGui->addColorPicker("leaf color", leafColor);
	datGui->addBreak();
	datGui->addColorPicker("bckground color", bckgroundColor);
	datGui->addBreak();
	datGui->addButton("save frame");
	datGui->addButton("default");
	datGui->addButton("exit");

	// once the gui has been assembled, register callbacks to listen for component specific events
	datGui->onButtonEvent(this, &ofApp::onButtonEvent);
	datGui->onToggleEvent(this, &ofApp::onToggleEvent);
	datGui->onTextInputEvent(this, &ofApp::onTextInputEvent);
	datGui->onDropdownEvent(this, &ofApp::onDropdownEvent);
	datGui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
	datGui->onSliderEvent(this, &ofApp::onSliderEvent);

	datGui->setVisible(true);
}

//--------------------------------------------------------------
void ofApp::drawBranch(int length) {

	ofSetColor(lineColor);
	ofDrawLine(0, 0, 0, -length);

	if (length > 4) { // protection against stack overflow
		ofPushMatrix();
		ofTranslate(0, -length);
		ofRotate(rightBranchAngle);
		drawBranch(lineLenCut * length);
		ofPopMatrix();

		ofPushMatrix();
		ofTranslate(0, -length);
		ofRotate(-leftBranchAngle);
		drawBranch(lineLenCut * length);
		ofPopMatrix();
	}
	else {
		if (bDrawLeaf) {
			drawLeaf(0, -length);
		}
	}
	ofSetColor(ofColor::white);
}

//--------------------------------------------------------------
void ofApp::drawLeaf(int x, int y) {
	ofSetColor(leafColor);
	if (bFillLeaf) {
		ofFill();
	}
	else {
		ofNoFill();
	}
	ofDrawCircle(x, y, leafRad);
	ofSetColor(ofColor::white);
}

//--------------------------------------------------------------
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e) {
}

//--------------------------------------------------------------
void ofApp::onToggleEvent(ofxDatGuiToggleEvent e) {
	ofLogVerbose("onToggleEvent") << e.target->getLabel() << " checked = " << e.checked << endl;
	if (e.target->is("draw leaf")) {
		bDrawLeaf = e.checked;
	}
	else if (e.target->is("fill leaf")) {
		bFillLeaf = e.checked;
	}
}

//--------------------------------------------------------------
void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e) {
	ofLogVerbose("onTextInputEvent") << "the input field changed to: " << e.text << endl;
}

//--------------------------------------------------------------
void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e) {
	ofLogNotice("onColorPickerEvent") << e.target->getLabel() << " " << e.target->getColor() << endl;
	if (e.target->is("bckground color")) {
		bckgroundColor = e.target->getColor();
	}
	else if (e.target->is("line color")) {
		lineColor = e.target->getColor();
	}
	else if (e.target->is("leaf color")) {
		leafColor = e.target->getColor();
	}
}

//--------------------------------------------------------------
void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
	ofLogVerbose("onSliderEvent") << e.target->getLabel() << " " << e.target->getName() << endl;

	if (e.target->is("line length")) {
		lineLen = e.target->getValue();
	}
	else if (e.target->is("line width")) {
		lineWidth = e.target->getValue();
	}
	else if (e.target->is("left angle")) {
		leftBranchAngle = e.target->getValue();
	}
	else if (e.target->is("right angle")) {
		rightBranchAngle = e.target->getValue();
	}
	else if (e.target->is("angle")) {
		rightBranchAngle = e.target->getValue();
		leftBranchAngle = e.target->getValue();
	}
	else if (e.target->is("line length cut")) {
		lineLenCut = e.target->getValue();
	}
	else if (e.target->is("leaf radius")) {
		leafRad = e.target->getValue();
	}
}

//--------------------------------------------------------------
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e) {
	ofLogVerbose("onButtonEvent") << e.target->getLabel() << endl;
	if (e.target->is("save frame")) {
		savePrintedImg();
	}
	else if (e.target->is("exit")) {
		ofExit();
	}
	else if (e.target->is("default")) {
		setDefault();
	}
}

//--------------------------------------------------------------
void ofApp::setDefault() {
	
	lineLen = 300;
	lineWidth = 2;
	lineLenCut = 0.63;
	bDrawLeaf = true;
	bFillLeaf = false;
	leafRad = 2;
	bothAngle = 45;
	leftBranchAngle = 45;
	rightBranchAngle = 45;
	lineColor = ofColor::white;
	bckgroundColor = ofColor::black;
	leafColor = ofColor::red;

	datGui->getSlider("line length")->setValue(lineLen);
	datGui->getSlider("line width")->setValue(lineWidth);
	datGui->getSlider("angle")->setValue(bothAngle);
	datGui->getSlider("left angle")->setValue(bothAngle);
	datGui->getSlider("right angle")->setValue(bothAngle);
	datGui->getColorPicker("bckground color")->setColor(bckgroundColor);
	datGui->getColorPicker("line color")->setColor(lineColor);
	datGui->getColorPicker("leaf color")->setColor(leafColor);
	datGui->getSlider("leaf radius")->setValue(leafRad);
	// todo set toogles
}
