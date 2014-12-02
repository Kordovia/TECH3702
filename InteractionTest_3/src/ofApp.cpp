#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(1280, 720);
    ofSetFrameRate(60);
    ofSetBackgroundAuto(true);
    ofBackground(0);
    
    grabber.setDeviceID(0);             //grab our first cam device
    grabber.setDesiredFrameRate(30);    //set framerate for cam
    grabber.initGrabber(1280, 720);      //set our incoming size
    
    image.allocate(grabber.width, grabber.height);  //allocate our CV ColorImage with w/h based off cam
    greyImage.allocate(grabber.width, grabber.height);  //same for other CV Images
    greyBackground.allocate(grabber.width, grabber.height); //same
    greyProcessed.allocate(grabber.width,grabber.height);   //same
    
    learnBackground = false;    //intially set to false
    
    
    lBKButton.addListener(this, &ofApp::bkToggler);    //setup a listener on our learn background button to toggle it's state momentarily
    guiStatus = true;   //set gui status to true
    
    gui.setup();    //setup the ofxPanel
    gui.add(lBKButton.setup("Learn Background"));
    gui.add(showProcessed.setup("Processed Image",true));
    gui.add(blurToggle.setup("Blur", false));
    gui.add(blurSlider.setup("Blur Amount",9,0,100));
    gui.add(errodeToggle.setup("Erode",true));
    gui.add(dilateToggle.setup("Dilate",true));
    gui.add(threshToggle.setup("Threshold", true));
    gui.add(threshSlider.setup("Threshold Amount",77,0,255));
    
    
    maxBlobs = 1;   //maximum number of blobs and size of our ofPoint vector
    
    blobCenters.resize(maxBlobs);   //set the size or our vector based off the numbe of blobs
    
    f = FireFliesTest3();
    //numFireFliesTest = 10;
    numFireFliesTest3 = 100;
    
    for(int i = 0; i <numFireFliesTest3; i++){
        FireFliesTest3 tempP = FireFliesTest3();
        firefliestest3.push_back(tempP);
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    grabber.update();   //pull our next frame of video
    
    image.setFromPixels(grabber.getPixelsRef());    //set our CV Color Image to have the same data as the current frame
    
    greyImage = image;  //convert our color image to grayscale
    
    //change the background comparision baseline if learnBackground is true
    if(learnBackground){
        greyBackground = greyImage;     //set the background to the current frame
        learnBackground = false;        //toggle back to false
    }
    
    greyDiff.absDiff(greyBackground, greyImage);    //do a comparison between our current background ref and current frame and store result in greyDiff
    
    greyProcessed = greyDiff;  //set our greyProcessed to be our greyDiff
    
    //toggle our various processing passes on and off
    if(blurToggle){
        greyProcessed.blur(blurSlider); //blur
    }
    if(errodeToggle){
        greyProcessed.erode();          //errode
    }
    if (dilateToggle) {
        greyProcessed.dilate();         //dilate
    }
    if(threshToggle){
        greyProcessed.threshold(threshSlider);   //threshold our image
    }
    
    //finding our contours on our processed image with a min size of 10 and max of half our screen size, looking for 1 blob, and looking for holes
    contourFinder.findContours(greyProcessed, 40, (grabber.width*grabber.height)/2, maxBlobs, true);
    
    
    //iterate through our blobs and pull the centroid and store as ofPoint
    for(int i = 0; i < contourFinder.nBlobs; i++){
        blobCenters[i] = contourFinder.blobs[i].centroid;
        
        
        
        
        f.seek();
        f.update();
        
        for(int i = 0; i <firefliestest3.size(); i++) {
            firefliestest3[i].seek();
            firefliestest3[i].update();
        }
        
        
        
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255,255,255);
    
    /*
     if (showProcessed) {
     image.draw(0,0);    //draw our color image
     }else{
     greyProcessed.draw(0,0);    //draw our processed greyscale image
     }
     */
    

    if (showProcessed) {
        image.draw(0,0);    //draw our color image
    }else{
        greyProcessed.draw(0,0);    //draw our processed greyscale image
    }
    
    //iterate through our blobs and draw them to the screen
    for(int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(0,0);
    }
    
    for(int i = 0; i < blobCenters.size(); i++){
      
        
        /*
        ofSetColor(0, 255, 0, 150);
        ofFill();
        ofCircle(blobCenters[i], 40);
        */
        

        float glowTime = ofGetElapsedTimef();       //returns time in seconds
        float value = sin(glowTime*1);
        //float v = ofMap(value, -1,1,0,255);     //map to 0-255 for RGB range
        float v = ofMap(value, -1,1,15,80);
        
        ofSetColor(245, 241, 0, v);                  //set the background to the mapped value of v
        //ofSetColor(245, 241, 0,30);             //outer glow
        ofFill();
        //ofCircle(0,0, ofRandom(5,12)*2.5, ofRandom(5,12)*2.5);
        ofCircle(blobCenters[i], ofRandom(5,7));
        
        ofSetColor(245, 241, 0, 100);           //inner glow
        ofFill();
        ofCircle(blobCenters[i], 3*2.5);
        
        ofSetColor(255,200);
        ofFill();
        ofCircle(blobCenters[i],3);      //white firefly
        
        
        
    }
    
    
    f.display();
    
    
    ofPoint loc = blobCenters[0];
    //ofPoint loc = ofPoint(ofRandom(0,ofGetWidth()), ofRandom(0,ofGetHeight())); //generate a random ofPoint on screen
    
    f.moveTarget(loc); //move the target for v to a new location and do so for the rest of our vehicles
    
    for(int i = 0; i < firefliestest3.size(); i++) {
        firefliestest3[i].moveTarget(loc);
    }
    
    
    
    for(int i = 0; i < firefliestest3.size(); i++) {
        firefliestest3[i].display();
    }
    
    
    /*
    
    //toggle gui
    if(guiStatus){
        gui.draw();     //draw our gui if toggled on
    }
     
     */
     
}

//function connected to the lBKToggle button
void ofApp::bkToggler(){
    learnBackground = true;     //if mouse is pressed then grab a new background plate
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key =='h') {
        guiStatus = !guiStatus; //flip our guistate
    }
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
