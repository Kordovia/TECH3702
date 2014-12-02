#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(1920, 1080);
    ofSetFrameRate(30);
    ofSetFullscreen(true);
    
    ofSetBackgroundAuto(true);
    //ofBackground(9, 0, 61);
    
    FireFlies01 tempP = FireFlies01();  //create a local BasicParticle to pass into our vector which will store BasicParticle objects
    
    particles.push_back(tempP);   //add a new BasicParticle to the rear of our vector
    
    //initializing our forces
    wind = ofPoint(-0.1,3.2);
    gravity = ofPoint(-0.4,0.0);
    
    counter = 0;    //counter used to trigger wind events
    maxParticles = 10; //set our max amount of particles
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(particles.size()<maxParticles){
        createNewParticle();        //create a new BasicParticle and place at the back of our vector
        //particleSizeChecker();      //check to see if there are too many particles in our vector
    }
    
    for(int i = 0; i < particles.size(); i++){      //iterate through our vector to update our BasicParticle Objects
        particles[i].applyForce(wind);      //pass our wind ofPoint and apply it on our particle via the applyForces method
        particles[i].applyForce(gravity);   //same for gravity
        
        particles[i].update();  //update our particle at location i within our vector
    }
    
    //ADD RANDOM WIND EVENT
    
     if (counter == 10) {
     wind.x = ofRandom(-1.0,1.0);
     wind.y = ofRandom(-1.0,1.0);
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
     
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //CHANGING BG
    float time = ofGetElapsedTimef();       //returns time in seconds
    //float time = ofGetElapsedTimeMillis();
    //float time = ofGetElapsedTimeMicros();
    
    //float value = sin(time*M_TWO_PI);       //get periodic value between -1 and 1 with a wavelength = 1sec
    //float value = sin(time*M_PI);
    float value = sin(time*.1);
    
    //float v = ofMap(value, -1,1,0,255);     //map to 0-255 for RGB range
    float v = ofMap(value, -1,1,10,90);
    
    ofBackground(0, 0, v);                  //set the background to the mapped value of v
    //------END OF CHANGING BG
    
    for(int i = 0; i < particles.size(); i++){      //iterate through our vector to draw our BasicParticle Objects
        particles[i].display();  //display our particle
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
    
}

//--------------particleSizeChecker--------------------
void ofApp::particleSizeChecker(){
    
    if(particles.size() > maxParticles){            //if there are over 1000 particles within our vector remove the oldest aka the 1st particle in the vector
        particles.erase(particles.begin());
    }
}
//------------END particleSizeChecker----------------------------

//---------------------createNewParticle-------------------------
void ofApp::createNewParticle(){
    FireFlies01 tempP = FireFlies01();  //create a local BasicParticle to pass into our vector which will store BasicParticle objects
    
    particles.push_back(tempP);   //add a new BasicParticle to the rear of our vector
}
//------------------End createNewParticle------------------------

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
