#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
 
    ofSetFrameRate(60);
    ofSetBackgroundAuto(true);
    ofBackground(0);
    ofSetFullscreen(true);
    
    grabber.setDeviceID(0);              //Grab first camera device
    grabber.setDesiredFrameRate(60);     //Set framerate
    grabber.initGrabber(1280, 720);      //Set incoming size of frame
    
    image.allocate(grabber.width, grabber.height);          //Allocate our CV ColorImage with w/h based off cam
    greyImage.allocate(grabber.width, grabber.height);
    greyBackground.allocate(grabber.width, grabber.height);
    greyProcessed.allocate(grabber.width,grabber.height);
    
    learnBackground = false;             //Do not learn background yet
    
    lBKButton.addListener(this, &ofApp::bkToggler);    //Able to toggle learn background
    guiStatus = false;                                 //Gui to False (Do not show)
    
    //Gui panel
    gui.setup();
    gui.add(lBKButton.setup("Learn Background"));
    gui.add(showProcessed.setup("Processed Image",true));
    gui.add(blurToggle.setup("Blur", false));
    gui.add(blurSlider.setup("Blur Amount",9,0,100));
    gui.add(errodeToggle.setup("Erode",true));
    gui.add(dilateToggle.setup("Dilate",true));
    gui.add(threshToggle.setup("Threshold", true));
    gui.add(threshSlider.setup("Threshold Amount",77,0,255));  //Threshold at specific amount
    
//Tracking blobs ---------------------------------------------------
    
    maxBlobs = 1;                   //Only track and create one blob
    blobCenters.resize(maxBlobs);   //Vector based on amount of blobs
    
//Tracking fireflies ---------------------------------------------------
    
    f = Fireflies01();
    numFireflies01 = 30;            //# of Fireflies that track blob
    
    for(int i = 0; i <numFireflies01; i++){
        Fireflies01 tempP = Fireflies01();
        fireflies01.push_back(tempP);
    }
    
//Wind fireflies (FRONT) ---------------------------------------------------
    
    //Fireflies in foreground of project
    Fireflies02 tempP = Fireflies02();  //Local fireflies that store as objects
    particles.push_back(tempP);         //Add new firefly to end of vector
    
    //Forces
    wind = ofPoint(-0.1,3.2);
    gravity = ofPoint(-0.4,0.0);
    
    counter = 10;       //Counter to trigger wind events
    maxParticles = 10;  //# of Fireflies affected by wind
    
    
//Wind fireflies (BACK) ---------------------------------------------------
    
    //Separate & smaller flies in background
    Fireflies03 tempB = Fireflies03();
    backparticles.push_back(tempB);
    
    backwind = ofPoint(-0.1, 3.2);
    backgravity = ofPoint (-0.4, 0.1);
    
    backcounter = 0;        //Separate counter for back fireflies
    backmaxParticles = 20;  //# of back Fireflies affected by wind

//Audio ---------------------------------------------------
    
    BackgroundMusic.loadSound("Music/EllinForest.mp3");
    BackgroundMusic.setLoop(true);      //Loop audio
    BackgroundMusic.play();
    
    //BackgroundMusic2.loadSound("Music/ElliniaTree.mp3");
    //BackgroundMusic2.setLoop(true);
    //BackgroundMusic2.play();
    
//Background Images ---------------------------------------------------
    
    BackgroundImage.loadImage("Photos/EnchantedForest.jpg");      //Image of background w/ stream & etc.
    ForegroundImage.loadImage("Photos/EnchantedForestFront.png"); //Image of cropped out trees
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSoundUpdate();    //Update sound
    grabber.update();   //Update video frames
    
    image.setFromPixels(grabber.getPixelsRef());    //Set CV Color Image to have the same data as the current frame
    
    greyImage = image;  //Convert our color image to grayscale
    
    //Change baseline if learnBackground is true
    if(learnBackground){
        greyBackground = greyImage;     //Set the background to the current frame
        learnBackground = false;        //Toggle back to false if learnBackground is in effect
    }
    
    greyDiff.absDiff(greyBackground, greyImage);    //do a comparison between our current background ref and current frame and store result in greyDiff
    
    greyProcessed = greyDiff;  //set our greyProcessed to be our greyDiff
    
    //Toggle various processing passes
    if(blurToggle){
        greyProcessed.blur(blurSlider); //Blur
    }
    if(errodeToggle){
        greyProcessed.erode();          //Errode
    }
    if (dilateToggle) {
        greyProcessed.dilate();         //Dilate
    }
    if(threshToggle){
        greyProcessed.threshold(threshSlider);   //Threshold image
    }
    
    contourFinder.findContours(greyProcessed, 40, (grabber.width*grabber.height)/2, maxBlobs, true);
    
    //Search through blob and pull the centroid and store as ofPoint
    for(int i = 0; i < contourFinder.nBlobs; i++){
        blobCenters[i] = contourFinder.blobs[i].centroid;
        
        
//Tracking fireflies ---------------------------------------------------
        
        f.seek();
        f.update();
        
        for(int i = 0; i <fireflies01.size(); i++) {
            fireflies01[i].seek();
            fireflies01[i].update();
        }
    }
    
    
//Wind fireflies (FRONT) ---------------------------------------------------
    
    if(particles.size()<maxParticles){
        createNewParticle();            //Place new basicParticle at the back of our vector
    }
    
    for(int i = 0; i < particles.size(); i++){
        particles[i].applyForce(wind);      //Apply wind
        particles[i].applyForce(gravity);   //Apply gravity
        particles[i].update();              //Update particle at location i within vector
    }
    
    //Random wind event for fireflies (FRONT)
    if (counter == 10) {
        wind.x = ofRandom(-1.0,1.0);
        wind.y = ofRandom(-1.0,1.0);
        learnBackground = true;             //Learn background at counter @ 10
        counter++;
        cout<<"RANDOM WIND EVENT"<<endl;
        cout<<"WIND = "<<wind.x<<","<<wind.y<<endl;
    }else if(counter > 1000){
        wind.x = 0.2;
        wind.y = 0.2;
        counter = 0;
        cout<<"WIND RESET"<<endl;
    }else{
        counter++;
    }
    
//Wind fireflies (BACK) ---------------------------------------------------
    
    if(backparticles.size()<backmaxParticles){
        backcreateNewParticle();
    }
    
    for (int i = 0; i < backparticles.size(); i++){
        backparticles[i].applyForce(backwind);
        backparticles[i].applyForce(backgravity);
        backparticles[i].update();
    }
    
    
    if (backcounter == 10) {
        backwind.x = ofRandom(-0.5,0.5);
        backwind.y = ofRandom(-0.5,0.5);
        backcounter++;
        cout<<"RANDOM BACKWIND EVENT"<<endl;
        cout<<"WIND = "<<backwind.x<<","<<backwind.y<<endl;
    }else if(backcounter > 100){
        backwind.x = 0.2;
        backwind.y = 0.2;
        backcounter = 0;
        cout<<"WIND RESET"<<endl;
    }else{
        backcounter++;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
//Time change ---------------------------------------------------
    
    float time = ofGetElapsedTimef();       //Returns time
    float value = sin(time*.1);
    float v = ofMap(value, -1,1,20,120);
    //v = change values throughout time
    
//Set BACKground image to change through time ---------------------------------------------------
    
    ofSetColor(v/2,v, v, v);            //Blue-green texture
    BackgroundImage.resize(1720, 1100); //1920x1200 - Stretched image
    BackgroundImage.draw(0,0);
    
//Draw fireflies in background ---------------------------------------------------
    
    for(int i = 0; i < backparticles.size(); i++){
        backparticles[i].display();
        
    }
    
//Draw FOREground image ---------------------------------------------------
    
    ofSetColor(130);
    ForegroundImage.resize(1720, 1100);
    ForegroundImage.draw(0,0);
    
    
    //Iterate through our blobs and draw them to the screen
    for(int i = 0; i < contourFinder.nBlobs; i++){
        // contourFinder.blobs[i].draw(0,0);
    }
    
    for(int i = 0; i < blobCenters.size(); i++){
        
        //Draw target
        ofSetColor(245, 241, 30, v*.5);
        ofFill();
        ofCircle(blobCenters[i], 3);
        
    }
    
//Draw tracking fireflies & target ---------------------------------------------------
    
    f.display();
    ofPoint loc = blobCenters[0];       //Change ofPoint to wherever blobCenters may be
    f.moveTarget(loc);                  //Move target for following fireflies/vehicles to follow
    
    for(int i = 0; i < fireflies01.size(); i++) {
        fireflies01[i].moveTarget(loc);
    }
    
    
    for(int i = 0; i < fireflies01.size(); i++) {
        fireflies01[i].display();
    }
    
    
//Draw wind fireflies ---------------------------------------------------
    
    for(int i = 0; i < particles.size(); i++){      //iterate through our vector to draw our BasicParticle Objects
        particles[i].display();                     //display our particle
    }
    
    
    /*
//Display gui ---------------------------------------------------
     
     //toggle gui
     if(guiStatus){
     gui.draw();     //draw our gui if toggled on
     }
     
     */
    
    
}

//Funciton to learnBackground ---------------------------------------------------
void ofApp::bkToggler(){
    learnBackground = false;     //if mouse is pressed then grab a new background plate
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    //Display gui
    //if (key =='h') {
    //    guiStatus = !guiStatus; //flip our guistate
    //}
    
    //Manually learn background by pressing 'b'
    if (key =='b') {
        learnBackground = true;
    }
    
}

//particleSizeChecker (FRONT FLIES) ---------------------------------------------------
void ofApp::particleSizeChecker(){
    
    //Delete if more than 1000 particles in vector, removes oldest (first particles in vector)
    if(particles.size() > maxParticles){
        particles.erase(particles.begin());
    }
}

//createNewParticle (FRONT FLIES) ---------------------------------------------------
void ofApp::createNewParticle(){
    
    Fireflies02 tempP = Fireflies02();  //Create local class
    particles.push_back(tempP);         //Add firefly to end of vector
}

//backparticleSizeChecker (BACK FIEs) ---------------------------------------------------
void ofApp::backparticleSizeChecker(){
    
    if(backparticles.size() > backmaxParticles){
        backparticles.erase(backparticles.begin());
    }
}

//backcreateNewParticle ---------------------------------------------------
void ofApp::backcreateNewParticle(){
    Fireflies03 tempB = Fireflies03();
    backparticles.push_back(tempB);
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
