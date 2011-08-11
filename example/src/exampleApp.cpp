#include "exampleApp.h"

//--------------------------------------------------------------
void exampleApp::setup(){
	ofSetWindowTitle("exampleApp");
	ofBackground(60);
	ofSetFrameRate(60);

	gui.registerOfEvents();
	gui.setPosition(100, 100);
	
	uTextEdit* tEdit = new uTextEdit();
	tEdit->setSingleline(true);
	gui.addChild(tEdit);
	
	/*
	tEdit = new uTextEdit();
	tEdit->setPosition(500, 0);
	gui.addChild(tEdit);
	 */
}

//--------------------------------------------------------------
void exampleApp::update(){
}

//--------------------------------------------------------------
void exampleApp::draw(){

}

//--------------------------------------------------------------
void exampleApp::keyPressed(int key){

}

//--------------------------------------------------------------
void exampleApp::keyReleased(int key){

}

//--------------------------------------------------------------
void exampleApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void exampleApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void exampleApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void exampleApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void exampleApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void exampleApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void exampleApp::dragEvent(ofDragInfo dragInfo){ 

}
