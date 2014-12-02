//
//  Fireflies03.cpp
//  Final_FirefliesProject002
//
//  Created by Kassey Cordova on 11/29/14.
//
//
//WIND FIREFLIES (BACK)
#include "Fireflies03.h"


Fireflies03::Fireflies03(){     //default constructor
    
    location = ofPoint(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));    //generate a random location to start from within the sketch window
    
    velocity = ofPoint(0,0);                                //starting with 0 instead
    
    acceleration = ofPoint(0.0,0.0);      //set acceleration to nothing to start so rely purely on incoming forces
    
    s = 2.5;     //scalar of our mass
    
    mass = ofRandom(0.9, 4);  //init mass as a random between 1-19.999...
}

void Fireflies03::update(){
    
    velocity = velocity+acceleration; //add acceleration to velocity to change over time
    
    velocity.limit(10); //limit velocity to 10. If our velocity hits 10 it will stay at 10.
    
    location = location+velocity;     //add velocity to location to move at a constant velocity.
    
    edgeCheck();    //if past the screen edge reset to opposite end of x or y
    
    
    acceleration*=0;    //scale acceleration by 0 and assign back to itself so forces do not continue to stack
}

void Fireflies03::applyForce(ofPoint f){
    ofPoint force = f/mass *-0.5 ;  //create/init ofPoint force which is set to the incoming force/mass per
    
    acceleration+=force;    //add and assign our force to acceleration, per accumulation of forces
}


void Fireflies03::display(){
    
    //Firefly glow
    float glowTime = ofGetElapsedTimef();
    float value = sin(glowTime*.5);
    float v = ofMap(value, -1,1,15,90);
    
    //Outerglow
    ofSetColor(245, 241, 0, v);
    ofFill();
    ofEllipse(location, ofRandom(2,5)*3, ofRandom(2,5)*3);
    
    //Innerglow
    ofSetColor(245, 241, 0, 100);
    ofFill();
    ofEllipse(location, 2*2, 2*2);
    
    //White firefly
    ofSetColor(255,200);
    ofFill();
    ofEllipse(location, 1.5,1.5);      
}


void Fireflies03::edgeCheck(){
    
    
    //do a bounds check for x. reset to opposite side of screen if out of bounds
    if(location.x > ofGetWidth()){
        location.x = ofGetWidth();
        velocity.x *= -1;       //flip our velocity if at left edge
    }else if(location.x < 0){
        location.x = 0;
        velocity.x *= -1;       //flip our velocity if at right edge
    }
    
    
    //do a bounds check for y. reset to opposite side of screen if out of bounds
    if(location.y > ofGetHeight()){
        location.y = ofGetHeight();
        velocity.y *= -1;      //flip our velocity if we hit the bottom edge
    }else if(location.y < 0){
        location.y = 0;
        velocity.y *= -1;       //flip our velocity if we hit the top edge
    }
}

