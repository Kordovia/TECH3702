#pragma once

#include "ofMain.h"
#include "FireFlies01.h"      //include our BasicParticle object header

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
    
    //BasicParticle p;        //BasicParticle object
    
    vector <FireFlies01> particles;       //Create a vector of particles. Similar to our Java ArrayList
    
    //forces
    ofPoint wind;   //ofPoint for the wind force
    ofPoint gravity;    //ofPoint for some fake gravity
    //end of forces
    
    int counter;    //counter to set when we have a random event
    int maxParticles;   //maximum number of particles
    
    void particleSizeChecker();     //Function to check the size of our particle array
    void createNewParticle();       //Function to create new particles for our vector of BasicParticle objects
    
    int frameNum;   //track the frame number for image sequence output
    
   // void recordIMGSeq();  //function to record the screen to an IMG Seq
};
