//
//  Fireflies02.cpp
//  Final_FirefliesProject002
//
//  Created by Kassey Cordova on 11/29/14.
//
//

//WIND FIREFLIES
#include "Fireflies02.h"


Fireflies02::Fireflies02(){     //default constructor
    
    location = ofPoint(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));    //generate a random location to start from within the sketch window
    
    velocity = ofPoint(0,0);                                //starting with 0 instead
    
    acceleration = ofPoint(0.0,0.0);      //set acceleration to nothing to start so rely purely on incoming forces
    
    s = 2.5;     //scalar of our mass
    
    mass = ofRandom(1,12);  //init mass as a random between 1-19.999...
}

void Fireflies02::update(){
    
    velocity = velocity+acceleration; //add acceleration to velocity to change over time
    
    velocity.limit(10); //limit velocity to 10. If our velocity hits 10 it will stay at 10.
    
    location = location+velocity;     //add velocity to location to move at a constant velocity.
    
    edgeCheck();    //if past the screen edge reset to opposite end of x or y
    
    acceleration*=0;    //scale acceleration by 0 and assign back to itself so forces do not continue to stack
}

void Fireflies02::applyForce(ofPoint f){
    ofPoint force = f/mass;  //create/init ofPoint force which is set to the incoming force/mass per
    
    acceleration+=force;    //add and assign our force to acceleration, per accumulation of forces
}


void Fireflies02::display(){
    
    //Firefly glow
    float glowTime = ofGetElapsedTimef();       //returns time in seconds
    float value = sin(glowTime*2);
    float v = ofMap(value, -1,1,15,80);
    
    //Outerglow
    ofSetColor(245, 241, 30, v);
    ofFill();
    ofEllipse(location, ofRandom(5,10)*2.5, ofRandom(5,10)*2.5);
    
    //Innerglow
    ofSetColor(245, 241, 0, 100);
    ofFill();
    ofEllipse(location, 3*2.5, 3*2.5);
    
    //White firefly
    ofSetColor(255,200);
    ofFill();
    ofEllipse(location, 3,3);
    
}


void Fireflies02::edgeCheck(){
    
    
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
