#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(1280, 720);
    ofSetFrameRate(60);
    ofSetBackgroundAuto(true);
    ofBackground(0, 100, 100);
    
    v = FireFlies04();  //init our new vehicle object
    
    numFireFlies04 = 10;  //number of vehicles in our vector
    
    
    for(int i = 0; i < numFireFlies04; i++){
        FireFlies04 tempP = FireFlies04();  //construct local vehicle
        fireflies04.push_back(tempP);    //create a new vehicle and place in vector
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    v.seek();   //calculate steering and apply force to affect acceleration
    v.update(); //update our position
    
    for(int i = 0; i < fireflies04.size(); i++) {
        fireflies04[i].seek();
        fireflies04[i].update();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    v.display();        //draw our vehicle
    
    
    for(int i = 0; i < fireflies04.size(); i++) {
        fireflies04[i].display();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ofPoint loc = ofPoint(ofRandom(0,ofGetWidth()), ofRandom(0,ofGetHeight())); //generate a random ofPoint on screen
    
    v.moveTarget(loc); //move the target for v to a new location and do so for the rest of our vehicles
    
    for(int i = 0; i < fireflies04.size(); i++) {
        fireflies04[i].moveTarget(loc);
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
