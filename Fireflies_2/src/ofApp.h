#pragma once

#include "ofMain.h"
#include "FireFlies02.h"        //include our vehicle header

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    FireFlies02 v;  //create a vehicle object
    
    int numFireFlies02;    //number of vehicles in our vector
    vector<FireFlies02> fireflies02;   //create a vecetor of vehicle objects
};
