#pragma once

#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "FireFlies03.h" 

class testApp : public ofBaseApp
{
public:
    static const unsigned NUM_BOXES = 100;
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    // scene stuff
    ofxPostProcessing post;
    ofEasyCam cam;
    ofLight light;
    
    // boxes
    vector<ofVec3f> posns;
    vector<ofColor> cols;
    ofVboMesh boxMesh;
    
    
    FireFlies03 v;  //create a vehicle object
    
    int numFireFlies03;    //number of vehicles in our vector
    vector<FireFlies03> fireflies03;   //create a vecetor of vehicle objects
    
};

