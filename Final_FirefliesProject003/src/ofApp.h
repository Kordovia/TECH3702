#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"
#include "Fireflies01.h"
#include "Fireflies02.h"
#include "Fireflies03.h"

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
    
//Video grabber ---------------------------------------------------
    
    ofVideoGrabber grabber;     //VideoGrabber for cam input
    
    ofxCvColorImage image;              //CV ColorImage for our cam input
    ofxCvGrayscaleImage greyImage;      //CV GreyscaleImage for conversion of our cam
    ofxCvGrayscaleImage greyBackground; //CV GreyscaleImage to store the background
    ofxCvGrayscaleImage greyDiff;       //CV GreyscaleImage to store the difference between the greyImage and greyBackground aka bk removal
    ofxCvGrayscaleImage greyProcessed;  //CV GreyscaleImage that is preprocessed prior to blob detection
    
    bool learnBackground;   //bool to set whether or not to look for a new background plate
    void bkToggler();       //function to toggle the background
    
    ofxCvContourFinder contourFinder;   //object for handling contour finding aka blobs
    
//Gui ---------------------------------------------------
    
    ofxPanel gui;               //ofxPanel object for gui objects
    ofxButton lBKButton;        //learn background Button
    ofxToggle showProcessed;    //toggle to show our RGB or Processed Image
    ofxToggle blurToggle;       //toggle for blur
    ofxIntSlider blurSlider;    //slider to control our blur amount
    ofxToggle errodeToggle;     //errosion toggle
    ofxToggle dilateToggle;     //toggle dilation
    ofxToggle threshToggle;     //thresholding toggle
    ofxIntSlider threshSlider;  //slider for setting threshold amount
    
    bool guiStatus;     //bool to toggle the gui draw
    
//Tracking blobs ---------------------------------------------------
    vector <ofPoint> blobCenters;   //ofPoints vector for our Blob centroids
    int maxBlobs;   //maximum number of blobs
    

//Target tracking fireflies ---------------------------------------------------
    
    Fireflies01 f;
    int numFireflies01;
    vector<Fireflies01> fireflies01;
    
//Wind fireflies (FRONT) ---------------------------------------------------
    
    vector <Fireflies02> particles;       //Create a vector of particles. Similar to our Java ArrayList
    
    //Forces
    ofPoint wind;       //ofPoint for the wind force
    ofPoint gravity;    //ofPoint for some fake gravity
    
    int counter;        //Counter to change event
    int maxParticles;   //Maximum number of particles
    
    void particleSizeChecker();     //Function to check the size of our particle array
    void createNewParticle();       //Function to create new particles for our vector of BasicParticle objects
    
    int frameNum;   //track the frame number for image sequence output
    
//Wind fireflies (BACK) ---------------------------------------------------
    
    vector <Fireflies03> backparticles;
    
    ofPoint backwind;
    ofPoint backgravity;
    
    int backcounter;
    int backmaxParticles;
    
    void backparticleSizeChecker();
    void backcreateNewParticle();
    
//Audio ---------------------------------------------------
    ofSoundPlayer   BackgroundMusic;
    ofSoundPlayer   BackgroundMusic2;
    
//Background Images ---------------------------------------------------
    ofImage    BackgroundImage;
    ofImage    ForegroundImage;
    
};
